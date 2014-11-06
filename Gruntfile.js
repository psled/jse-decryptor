/**
 * Gruntfile
 */

'use strict';

module.exports = function (grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),
    encrypt: {
      options: {
        key: 'secretphrase',
        ext: 'jse',
        dest: './build/'
      },
      files: ['./lib/**/*.js']      
    }    
  });

  grunt.loadNpmTasks('grunt-encrypt');

  grunt.registerTask('default', ['encrypt']);
};
