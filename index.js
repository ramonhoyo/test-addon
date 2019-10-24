const testAddon = require('./build/Release/testaddon.node');
const fs = require('fs');

console.time('Program runtime');

console.log('addon',testAddon);
console.log(testAddon.hello());
console.log(testAddon.add(2, 5));

const classInstance = new testAddon.ActualClass(2.32);
console.log("initial value: ", classInstance.getValue());
console.log("after adding 2.3", classInstance.add(2.3));

const buf = fs.readFileSync('test-data');

if(buf === undefined || buf === null){
    console.log("error readding file");
}

console.log("size of buffer: ",buf.length);

console.time('Time spent by native addon on main event loop thread');
console.time('Data manipulation');

testAddon.ProcessData(buf, (p) => {
    console.log(p);
    console.timeEnd('Data manipulation');
    fs.writeFileSync('test-data-modified', buf);
    console.timeEnd('Program runtime');
});

console.timeEnd('Time spent by native addon on main event loop thread');
 
module.exports = testAddon;