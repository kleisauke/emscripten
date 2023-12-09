// N.B. The contents of this file are duplicated in src/library_wasm_worker.js
// in variable "_wasmWorkerBlobUrl" (where the contents are pre-minified) If
// doing any changes to this file, be sure to update the contents there too.

'use strict';

#if ENVIRONMENT_MAY_BE_NODE
// Node.js support
var ENVIRONMENT_IS_NODE = typeof process == 'object' && typeof process.versions == 'object' && typeof process.versions.node == 'string';
if (ENVIRONMENT_IS_NODE) {
  // Create as web-worker-like an environment as we can.

  var { Worker, parentPort } = require('node:worker_threads');

  parentPort.on('message', (data) => typeof onmessage === "function" && onmessage({ data: data }));

  var fs = require('node:fs');

  Object.assign(global, {
    self: global,
    require,
    location: {
      href: __filename
    },
    Worker,
    importScripts: (f) => (0, eval)(fs.readFileSync(f, 'utf8') + '//# sourceURL=' + f),
    postMessage: (msg) => parentPort.postMessage(msg),
    performance: global.performance || { now: Date.now },
    addEventListener: (name, handler) => parentPort.on(name, handler),
    removeEventListener: (name, handler) => parentPort.off(name, handler),
  });
}
#endif // ENVIRONMENT_MAY_BE_NODE

{{{ implicitSelf() }}}onmessage = function(d) {
	// The first message sent to the Worker is always the bootstrap message.
	// Drop this message listener, it served its purpose of bootstrapping
	// the Wasm Module load, and is no longer needed. Let user code register
	// any desired message handlers from now on.
	{{{ implicitSelf() }}}onmessage = null;
	d = d.data;
#if !MODULARIZE
	self.{{{ EXPORT_NAME }}} = d;
#endif
#if !MINIMAL_RUNTIME
	d['instantiateWasm'] = (info, receiveInstance) => { var instance = new WebAssembly.Instance(d['wasm'], info); return receiveInstance(instance, d['wasm']); }
#endif
	importScripts(d.js);
#if MODULARIZE
	{{{ EXPORT_NAME }}}(d);
#endif
	// Drop now unneeded references to from the Module object in this Worker,
	// these are not needed anymore.
	d.wasm = d.mem = d.js = 0;
}
