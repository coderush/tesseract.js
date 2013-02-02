var tesseractjs = require('../lib/tesseract')
var t = new tesseractjs.TesseractBinding();
console.log("Object created");
t.init("eng");
t.setImage(__dirname + "/images/test-image.jpg");
t.processImage();
console.log(t.getText());
t.close();
t.end();