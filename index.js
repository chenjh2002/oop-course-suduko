import {Suduko} from './src/suduko.js';

let suduko = Suduko.parse("009000080601902007000000006000003040008705200040600000500000000300009001060000720", 9);
let ans = suduko.getInference();

for (let i = 0; i < ans.length; i++) {
  const rowString = ans[i].join(' ');
  console.log(rowString);
}