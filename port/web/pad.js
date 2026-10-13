// Controller status and tester for the landing page: the header chip shows
// whether a gamepad is connected, and the diagram on the Ready panel lights up
// with what the game will see from it (or from the keyboard).
'use strict';

const MssbPad = (() => {
  const $ = (id) => document.getElementById(id);

  // Browser "standard" gamepad layout -> GameCube buttons, matching aurora's
  // default mappings (dolphin/pad/pad.cpp). Xbox pads put B and X the other way
  // round so B sits left of A, as on a GameCube pad.
  const STANDARD = { 0: 'a', 1: 'b', 2: 'x', 3: 'y', 9: 'start', 5: 'z', 12: 'up', 13: 'down', 14: 'left', 15: 'right' };
  const XBOX = { ...STANDARD, 1: 'x', 2: 'b' };

  // The keyboard bindings listed on the page.
  const KEYS = {
    KeyX: 'a', KeyZ: 'b', KeyC: 'x', KeyV: 'y', Enter: 'start', ShiftLeft: 'z', ShiftRight: 'z', KeyQ: 'l', KeyE: 'r',
    KeyI: 'up', KeyK: 'down', KeyJ: 'left', KeyL: 'right',
  };
  const KEY_AXES = {
    ArrowLeft: ['main', 0, -1], ArrowRight: ['main', 0, 1], ArrowUp: ['main', 1, -1], ArrowDown: ['main', 1, 1],
    KeyA: ['c', 0, -1], KeyD: ['c', 0, 1], KeyW: ['c', 1, -1], KeyS: ['c', 1, 1],
  };
  const keysDown = new Set();

  function isXbox(pad) {
    return /xbox|xinput|045e/i.test(pad.id);
  }

  function padName(pad) {
    // Chrome: "Xbox 360 Controller (XInput STANDARD GAMEPAD)",
    // "DualSense Wireless Controller (STANDARD GAMEPAD Vendor: 054c Product: 0ce6)".
    const name = pad.id.replace(/\s*\(.*\)\s*$/, '').trim();
    return name || 'Controller';
  }

  function connectedPads() {
    return [...(navigator.getGamepads?.() || [])].filter((p) => p && p.connected);
  }

  // ---- Header chip ----------------------------------------------------------

  let chipKey = null;
  function renderChip() {
    const pads = connectedPads();
    const key = pads.map((p) => p.id).join('\n');
    if (key === chipKey) return;
    chipKey = key;
    const chip = $('pad-chip');
    chip.classList.toggle('on', pads.length > 0);
    chip.querySelector('.label').textContent = pads.length
      ? pads.length > 1 ? `${pads.length} controllers` : `${padName(pads[0])} connected`
      : 'No controller';
    chip.title = pads.length ? pads.map((p, i) => `Player ${i + 1}: ${p.id}`).join('\n') : 'Plug in a controller and press a button';
  }

  // ---- Tester -----------------------------------------------------------------

  function readState() {
    const s = { pressed: new Set(), main: [0, 0], c: [0, 0], l: 0, r: 0, source: null };
    const pad = connectedPads()[0];
    if (pad) {
      const map = isXbox(pad) ? XBOX : STANDARD;
      pad.buttons.forEach((b, i) => {
        if (b.pressed && map[i]) s.pressed.add(map[i]);
      });
      const ax = (i) => (Math.abs(pad.axes[i] || 0) > 0.12 ? pad.axes[i] : 0);
      s.main = [ax(0), ax(1)];
      s.c = [ax(2), ax(3)];
      s.l = Math.max(pad.buttons[6]?.value || 0, pad.buttons[4]?.pressed ? 1 : 0);
      s.r = pad.buttons[7]?.value || 0;
      if (s.pressed.size || s.l > 0.05 || s.r > 0.05 || s.main.some(Boolean) || s.c.some(Boolean)) s.source = padName(pad);
    }
    if (keysDown.size) {
      for (const code of keysDown) {
        if (KEYS[code] === 'l') s.l = 1;
        else if (KEYS[code] === 'r') s.r = 1;
        else if (KEYS[code]) s.pressed.add(KEYS[code]);
        const a = KEY_AXES[code];
        if (a) s[a[0]][a[1]] = a[2];
      }
      s.source ??= 'Keyboard';
    }
    return { s, pad };
  }

  let svg = null;
  let running = false;
  let lastSource = '';

  function frame() {
    if (!running) return;
    const { s, pad } = readState();
    for (const el of svg.querySelectorAll('[data-btn]')) el.classList.toggle('on', s.pressed.has(el.dataset.btn));
    const stick = (id, [x, y], reach) => {
      const el = svg.getElementById(id);
      el.setAttribute('transform', `translate(${(x * reach).toFixed(1)} ${(y * reach).toFixed(1)})`);
      el.classList.toggle('on', x !== 0 || y !== 0);
    };
    stick('pad-main', s.main, 11);
    stick('pad-c', s.c, 8);
    svg.getElementById('pad-l-fill').setAttribute('width', (34 * s.l).toFixed(1));
    svg.getElementById('pad-r-fill').setAttribute('width', (34 * s.r).toFixed(1));
    svg.getElementById('pad-l-fill').setAttribute('x', (60 - 34 * s.l).toFixed(1));

    const status = $('pad-status');
    if (s.source) lastSource = s.source;
    const text = pad
      ? `${padName(pad)} — player 1`
      : 'No controller found. Plug one in and press a button.';
    status.textContent = text;
    $('pad-test').classList.toggle('connected', !!pad);
    $('pad-input').textContent = s.source
      ? `Input from ${s.source}`
      : lastSource ? `Last input: ${lastSource}` : 'Press buttons, move the sticks, or use the keyboard.';
    requestAnimationFrame(frame);
  }

  function onKey(e) {
    if (!running || e.target.closest?.('input, select, textarea')) return;
    if (e.type === 'keydown') keysDown.add(e.code);
    else keysDown.delete(e.code);
  }

  function init() {
    svg = $('pad-svg');
    renderChip();
    addEventListener('gamepadconnected', renderChip);
    addEventListener('gamepaddisconnected', renderChip);
    // Chrome only reports a pad after a button press; poll so the chip catches it.
    setInterval(renderChip, 1000);
    addEventListener('keydown', onKey);
    addEventListener('keyup', onKey);
    addEventListener('blur', () => keysDown.clear());
  }

  // The tester only runs while the Ready panel is up.
  function setActive(on) {
    if (on === running) return;
    running = on;
    keysDown.clear();
    if (on) requestAnimationFrame(frame);
  }

  return { init, setActive };
})();
