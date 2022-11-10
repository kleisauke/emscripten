/*
 * Copyright 2012 The Closure Compiler Authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @fileoverview Definitions for node:module.
 * @see https://nodejs.org/api/module.html
 * @see https://github.com/nodejs/node/blob/f313b39d8f282f16d36fe99372e919c37864721c/lib/internal/modules/cjs/loader.js
 * @externs
 * @author Kleis Auke Wolthuizen <github@kleisauke.nl>
 */

/**
 BEGIN_NODE_INCLUDE
 var module = require('module');
 END_NODE_INCLUDE
 */

/**
 * @type {Object.<string,*>}
 * @suppress {duplicate}
 */
var module = {};

/**
 * @type {Array.<string>}
 */
module.builtinModules;

/**
 * @param {string|url.URL} filename
 * @return {function(string)}
 * @nosideeffects
 */
module.createRequire = function(filename) {};

/**
 * @param {string} moduleName
 * @return {boolean}
 * @nosideeffects
 */
module.isBuiltin = function(moduleName) {};

/**
 * @nosideeffects
 */
module.syncBuiltinESMExports = function() {};

// Source map v3 types omitted, as that is currently considered to be experimental
// https://nodejs.org/api/module.html#source-map-v3-support
