// Dolphin SDK DSP API on top of the audio microcode HLE (dsp_ax.cpp).
//
// There is no DSP to boot: a task is ready as soon as it's added. Its init
// callback is raised like the DSP interrupt would: from another thread in
// interrupt context, i.e. once the adding thread re-enables interrupts (MusyX
// adds the task with interrupts disabled, clears its "init done" flag, then
// enables them and spins on the flag). Every command list mailed to the task
// runs synchronously on the mailing thread. MusyX's mail protocol is
// two mails per 5 ms frame: 0xBABExxxx (xxxx = size of the first list chunk),
// then the list's physical address. Once the list has run, the task's resume
// callback fires, as the DSP interrupt would after the ucode yields.
//
// MusyX mails from its AI DMA callback, which ai.cpp runs on the SDL audio
// thread in interrupt context, so the mixer runs there too.

#include <dolphin/dsp.h>

#include "dsp_ax.h"

#include "port/os.h"

#include <thread>

namespace {
enum class MailState
{
    Idle,        // waiting for 0xBABExxxx
    WaitAddress, // waiting for the command list address
};

BOOL s_initialized = FALSE;
bool s_halted = false;
DSPTaskInfo* s_task = nullptr;
MailState s_mailState = MailState::Idle;

constexpr u32 kTaskStateRunning = 1;
constexpr u32 kTaskStateDone = 3;

void run_callback(DSPCallback cb, DSPTaskInfo* task)
{
    if (cb != nullptr)
        cb(task);
}
} // namespace

extern "C" {
void DSPInit(void)
{
    if (s_initialized)
        return;
    s_initialized = TRUE;
    s_halted = false;
    s_task = nullptr;
    s_mailState = MailState::Idle;
    dsp_ax_reset();
}

BOOL DSPCheckInit(void) { return s_initialized; }

void DSPReset(void)
{
    s_mailState = MailState::Idle;
    s_halted = false;
    dsp_ax_reset();
}

void DSPHalt(void) { s_halted = true; }

void DSPUnhalt(void) { s_halted = false; }

u32 DSPGetDMAStatus(void) { return 0; }

void DSPAssertInt(void) {}

// The CPU->DSP mailbox is always drained immediately.
u32 DSPCheckMailToDSP(void) { return 0; }

u32 DSPReadCPUToDSPMbox(void) { return 0; }

// Nothing is ever mailed back; completion is signalled with callbacks.
u32 DSPCheckMailFromDSP(void) { return 0; }

u32 DSPReadMailFromDSP(void) { return 0; }

void DSPSendMailToDSP(u32 mail)
{
    switch (s_mailState)
    {
    case MailState::Idle:
        if ((mail >> 16) == 0xBABE)
            s_mailState = MailState::WaitAddress;
        break;
    case MailState::WaitAddress:
        s_mailState = MailState::Idle;
        if (!s_halted)
            dsp_ax_execute(mail);
        if (s_task != nullptr)
            run_callback(s_task->res_cb, s_task);
        break;
    }
}

DSPTaskInfo* DSPAddTask(DSPTaskInfo* task)
{
    if (task == nullptr)
        return nullptr;
    task->state = kTaskStateRunning;
    task->next = nullptr;
    task->prev = nullptr;
    s_task = task;
    s_mailState = MailState::Idle;
    if (task->init_cb != nullptr)
    {
#ifdef __EMSCRIPTEN__
        port_raise_interrupt([](void* arg) {
            auto* t = static_cast<DSPTaskInfo*>(arg);
            run_callback(t->init_cb, t);
        }, task);
        return task;
#endif
        std::thread([task] {
            port_interrupt_enter();
            run_callback(task->init_cb, task);
            port_interrupt_leave();
        }).detach();
    }
    return task;
}

DSPTaskInfo* DSPCancelTask(DSPTaskInfo* task)
{
    if (task == nullptr)
        return nullptr;
    task->state = kTaskStateDone;
    if (s_task == task)
    {
        s_task = nullptr;
        s_mailState = MailState::Idle;
    }
    run_callback(task->done_cb, task);
    return task;
}

DSPTaskInfo* DSPAssertTask(DSPTaskInfo* task) { return task; }

DSPTaskInfo* __DSPGetCurrentTask(void) { return s_task; }
}
