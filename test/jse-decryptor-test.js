/**
 * JSE Decryptor Test
 */

// load native module
var addon = require('../build/Release/addon');

// create an instance of JSE Decryptor
var jseDecryptor = new addon.JSEDecryptor();

// register '.jse' extension
require.extensions[".jse"] = function (m) {
  m.exports = jseDecryptor.decrypt(m);
};

// load encrypted module
var ConfidentialItem = require("../build/lib/confidentialitem");

// create an instance of encrypted module
var confItem = new ConfidentialItem();

// access property from encrypted module
console.log(confItem.secretMessage);
