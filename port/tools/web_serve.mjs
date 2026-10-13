#!/usr/bin/env node
// Serves the web build (build/web) on http://localhost:8080.
// Also serves a disc image at /disc.iso with Range support (for ?iso=disc.iso
// test runs that skip the file picker): MSSB_ISO=path, default
// ../mario_baseball.iso next to the repo.
//   node port/tools/web_serve.mjs [port]
import { createServer } from 'node:http';
import { createReadStream, statSync, existsSync } from 'node:fs';
import { extname, join, normalize, resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '../..');
const webDir = process.env.MSSB_WEB_DIR ? resolve(process.env.MSSB_WEB_DIR) : join(root, 'build/web'); // MSSB_WEB_DIR: another build (e.g. a debug one)
const iso = process.env.MSSB_ISO || [join(root, 'mario_baseball.iso'), join(root, '../mario_baseball.iso'), join(root, '../../mario_baseball.iso'), join(root, '../../../mario_baseball.iso')].find((p) => existsSync(p)) || join(root, 'mario_baseball.iso');
const port = Number(process.argv[2] || 8080);
const types = {
  '.html': 'text/html; charset=utf-8',
  '.js': 'text/javascript; charset=utf-8',
  '.wasm': 'application/wasm',
  '.iso': 'application/octet-stream',
};

createServer((req, res) => {
  const url = new URL(req.url, 'http://localhost');
  let path = decodeURIComponent(url.pathname);
  if (path === '/') path = '/index.html';
  const safe = normalize(path).replace(/^(\.\.[/\\])+/, '');
  const file = path === '/disc.iso' ? iso
    : join(webDir, safe);
  if (!existsSync(file) || !statSync(file).isFile()) {
    console.log(`404 ${path}`);
    res.writeHead(404).end('not found');
    return;
  }
  // Which browser loaded the page (helps with "works for me" reports).
  if (path === '/index.html') console.log(`page ${req.socket.remoteAddress} ${req.headers['user-agent'] || ''}`);
  const size = statSync(file).size;
  const headers = {
    'Content-Type': types[extname(file)] || 'application/octet-stream',
    'Accept-Ranges': 'bytes',
    'Cache-Control': 'no-cache',
  };
  const range = /^bytes=(\d+)-(\d*)$/.exec(req.headers.range || '');
  if (range) {
    const start = Number(range[1]);
    const end = range[2] ? Math.min(Number(range[2]), size - 1) : size - 1;
    res.writeHead(206, { ...headers, 'Content-Range': `bytes ${start}-${end}/${size}`, 'Content-Length': end - start + 1 });
    if (req.method === 'HEAD') return res.end();
    createReadStream(file, { start, end }).pipe(res);
    return;
  }
  res.writeHead(200, { ...headers, 'Content-Length': size });
  if (req.method === 'HEAD') return res.end();
  createReadStream(file).pipe(res);
}).listen(port, () => console.log(`Mario Superstar Baseball: http://localhost:${port}/ (disc: ${iso})`));
