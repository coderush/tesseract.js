tesseract.js
============

Javascript wrapper for tesseract OCR 

Install
-------

    [sudo] npm install [-g] tesseract-js

Features
--------


Version History
---------------

*  v0.0.1 - First release

Usage
-----

```javascript
var tesseractjs = require('../lib/tesseract')
var t = new tesseractjs.TesseractBinding();
console.log("Object created");
t.init("eng");
t.setImage(__dirname + "/images/test-image.jpg");
t.processImage();
console.log(t.getText());
t.close();
t.end();
```

Testing
-------

    npm test


TODO
----


License
-------

Licensed under the incredibly [permissive](http://en.wikipedia.org/wiki/Permissive_free_software_licence) [MIT License](http://creativecommons.org/licenses/MIT/). Copyright &copy; 2012 Sumit Ranjan.