Code protection for Node.js
===

### Why:

Because releasing a JavaScript source code as a plain text is not always the best idea. Inspiration taken from a [stackoveflow answer](http://stackoverflow.com/questions/5951302/node-js-code-protection).

However, be aware that this is rather an unfinished proof of concept and security mockup than a real protection mechanism. If anybody really wants to discover your JavaScript source code he or she will easily do this, no matter how much effort you put into protecting it.

### Requirements:

    * node-gyp
    * grunt-cli

### To build:

```sh
npm update
node-gyp rebuild
grunt
```

The order of last two commands matters (!) - at least with the default Grunt config file.

### To run the test:

```sh
node .
```
