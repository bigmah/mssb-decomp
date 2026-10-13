// On-screen touch controls for phones and tablets: a floating analog stick on
// the left half of the screen and GameCube-style buttons on the right. The
// state goes to the game as port 1's pad (Module.mssbTouch, read each
// frame by port/web/src/net_web.cpp), on top of any keyboard or gamepad.
'use strict';

const MssbTouch = (() => {
  const $ = (id) => document.getElementById(id);

  // dolphin/pad.h
  const MASK = { left: 0x1, right: 0x2, down: 0x4, up: 0x8, z: 0x10, r: 0x20, l: 0x40,
    a: 0x100, b: 0x200, x: 0x400, y: 0x800, start: 0x1000 };
  const STICK_RADIUS = 56; // px the knob travels
  const DEAD_ZONE = 0.12;

  const state = { active: false, bytes: new Uint8Array(8) };
  let root = null;
  let enabled = false;
  let stick = null; // {id, x0, y0, x, y}
  const buttonPointers = new Map(); // pointerId -> button name

  // NetPad layout: u16 buttons, s8 stickX, stickY, substickX, substickY, u8 triggerL, triggerR.
  function publish() {
    let buttons = 0;
    for (const name of buttonPointers.values()) buttons |= MASK[name];
    let sx = 0;
    let sy = 0;
    if (stick) {
      let dx = (stick.x - stick.x0) / STICK_RADIUS;
      let dy = (stick.y - stick.y0) / STICK_RADIUS;
      const mag = Math.hypot(dx, dy);
      if (mag > 1) {
        dx /= mag;
        dy /= mag;
      }
      if (mag > DEAD_ZONE) {
        sx = Math.round(dx * 100);
        sy = Math.round(-dy * 100); // pad Y is up
      }
    }
    const b = state.bytes;
    b[0] = buttons & 0xff;
    b[1] = buttons >> 8;
    b[2] = sx & 0xff;
    b[3] = sy & 0xff;
    b[4] = b[5] = 0;
    b[6] = buttons & MASK.l ? 200 : 0;
    b[7] = buttons & MASK.r ? 200 : 0;
    state.active = buttons !== 0 || sx !== 0 || sy !== 0;
    for (const el of root.querySelectorAll('.tbtn')) el.classList.toggle('down', !!(buttons & MASK[el.dataset.btn]));
  }

  function buzz() {
    try {
      navigator.vibrate?.(8);
    } catch {}
  }

  // The button under a point, so a thumb can roll from A onto B.
  function buttonAt(x, y) {
    const el = document.elementFromPoint(x, y)?.closest?.('.tbtn');
    return el && root.contains(el) ? el.dataset.btn : null;
  }

  function renderStick() {
    const base = $('t-stick');
    if (!stick) {
      base.classList.remove('on');
      base.style.transform = '';
      $('t-knob').style.transform = '';
      return;
    }
    const box = root.getBoundingClientRect();
    base.classList.add('on');
    base.style.transform = `translate(${stick.x0 - box.left}px, ${stick.y0 - box.top}px)`;
    let dx = stick.x - stick.x0;
    let dy = stick.y - stick.y0;
    const mag = Math.hypot(dx, dy);
    if (mag > STICK_RADIUS) {
      dx *= STICK_RADIUS / mag;
      dy *= STICK_RADIUS / mag;
    }
    $('t-knob').style.transform = `translate(${dx}px, ${dy}px)`;
  }

  function onDown(e) {
    if (e.pointerType === 'mouse' && !enabled) return;
    const btn = buttonAt(e.clientX, e.clientY);
    if (btn) {
      buttonPointers.set(e.pointerId, btn);
      buzz();
    } else if (!stick && e.clientX < window.innerWidth / 2) {
      stick = { id: e.pointerId, x0: e.clientX, y0: e.clientY, x: e.clientX, y: e.clientY };
      renderStick();
    } else {
      return;
    }
    e.preventDefault();
    root.setPointerCapture?.(e.pointerId);
    publish();
  }

  function onMove(e) {
    if (stick && e.pointerId === stick.id) {
      stick.x = e.clientX;
      stick.y = e.clientY;
      renderStick();
      publish();
    } else if (buttonPointers.has(e.pointerId)) {
      const btn = buttonAt(e.clientX, e.clientY);
      if (btn && btn !== buttonPointers.get(e.pointerId)) {
        buttonPointers.set(e.pointerId, btn);
        buzz();
        publish();
      }
    }
  }

  function onUp(e) {
    if (stick && e.pointerId === stick.id) {
      stick = null;
      renderStick();
    }
    buttonPointers.delete(e.pointerId);
    publish();
  }

  function releaseAll() {
    stick = null;
    buttonPointers.clear();
    if (root) {
      renderStick();
      publish();
    }
  }

  function setEnabled(on) {
    enabled = on;
    document.body.classList.toggle('touch', on);
    if (!on) releaseAll();
  }

  function init(params) {
    root = $('touch');
    window.Module = window.Module || {};
    Module.mssbTouch = state;
    root.addEventListener('pointerdown', onDown);
    root.addEventListener('pointermove', onMove);
    root.addEventListener('pointerup', onUp);
    root.addEventListener('pointercancel', onUp);
    root.addEventListener('contextmenu', (e) => e.preventDefault());
    window.addEventListener('blur', releaseAll);
    document.addEventListener('visibilitychange', releaseAll);

    // Show the controls on touch screens (or with ?touch), and hide them once a
    // gamepad or the keyboard is used instead; touching the screen brings them back.
    const coarse = matchMedia('(pointer: coarse)').matches;
    setEnabled(params.has('touch') || (coarse && !params.has('notouch')));
    window.addEventListener('touchstart', () => {
      if (!enabled && !params.has('notouch')) setEnabled(true);
    }, { passive: true });
    window.addEventListener('gamepadconnected', () => {
      if (!params.has('touch')) setEnabled(false);
    });
    window.addEventListener('keydown', (e) => {
      if (!params.has('touch') && !e.target.closest?.('input, select, textarea')) setEnabled(false);
    });
  }

  return { init, isEnabled: () => enabled };
})();
