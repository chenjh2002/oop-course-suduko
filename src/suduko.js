import {Grid} from './grid.js';

export class Suduko extends Grid {

  /**
   *
   * @param grid {Number [][]}
   * @param GRID_SIZE {Number}
   * @param BOX_SIZE {Number}
   */
  constructor(emptyHole, grid, GRID_SIZE, BOX_SIZE) {
    super(grid, GRID_SIZE, BOX_SIZE);
    this.emptyHole = emptyHole;
    this.ans = Array.from({length : GRID_SIZE},
        (_, __) =>
            Array.from({length : GRID_SIZE}, (_, __) => Number(0)));
    this.pathRecord = Array.from({length : emptyHole.length},
        (_, __) => new Set());
  }

  /**
   *
   * @param str {String}
   * @param sudukoSize {Number}
   * @return {Suduko}
   */
  static parse(str, sudukoSize) {
    this._checkStr(str, sudukoSize);

    const grid = [];
    const emptyHole = [];
    for (let row = 0; row < sudukoSize; row++) {
      const rowAttr = [];
      for (let col = 0; col < sudukoSize; col++) {
        const val = str[row * sudukoSize + col];
        rowAttr.push(parseInt(val));
        if (parseInt(val) === 0) {
          emptyHole.push([row, col]);
        }
      }

      grid.push(rowAttr);
    }

    return new Suduko(emptyHole, grid, sudukoSize, Math.sqrt(sudukoSize));
  }

  static _checkStr(str, sudukoSize) {
    if (Math.sqrt(sudukoSize) % 1 !== 0) {
      throw new Error(
          'Invalid suduko size, suduko size must be a square number.');
    }

    const regex = new RegExp(`[0-9]{${sudukoSize ** 2}}`);
    if (!regex.test(str)) {
      throw new Error('Invalid suduko string');
    }
  }

  /**
   *
   * @returns {Number[][]}
   */
  getInitialInference() {
    const inference = []
    for (let row = 0; row < this.grid.length; row++) {
      const rowArr = []
     for (let col = 0; col < this.grid.length; col++) {
       const cell = this.grid[row][col];
       if (cell === 0) {
         const candidates = this.getCandidate(row, col);
         rowArr.push(candidates);
       } else {
         rowArr.push([cell]);
       }
     }
     inference.push(rowArr);
    }

    return inference;
  }

  /**
   *
   * @param row {Number}
   * @param col {Number}
   * @return {Number[]}
   */
  getCandidate(row, col) {
    let candidates = Array.from({length: this.grid.length}, (_, i) => i + 1);
    const sameRow = this.grid[row] + this.ans[row];
    const sameCol = this.grid.map(row => row[col]) + this.ans.map(row => row[col]);
    // Same Box
    const boxSize = Math.sqrt(this.grid.size);
    const boxStartRow = Math.floor(row / this.BOX_SIZE) * this.BOX_SIZE;
    const boxStartCol = Math.floor(col / this.BOX_SIZE) * this.BOX_SIZE;
    const sameBox = [];
    for (let r = boxStartRow; r < boxStartRow + this.BOX_SIZE; r++) {
      for (let c = boxStartCol; c < boxStartCol + this.BOX_SIZE; c++) {
        sameBox.push(this.grid[r][c]);
        sameBox.push(this.ans[r][c]);
      }
    }

    const excludeValue = new Set([...sameRow, ...sameCol, ...sameBox]);
    candidates = candidates.filter(candidate => !excludeValue.has(candidate));
    return candidates;
  }

  /**
   * @return {Number[][]}
   */
  getInference() {
    let dfsIndex = 0;
    while (dfsIndex < this.emptyHole.length) {
      let candidates = this.getCandidate(this.emptyHole[dfsIndex][0], this.emptyHole[dfsIndex][1]);
      if (candidates.length === 0) {
        dfsIndex--;
        this.ans[this.emptyHole[dfsIndex][0]][this.emptyHole[dfsIndex][1]] = 0;
        continue;
      }

      candidates = candidates.filter(candidate => !this.pathRecord[dfsIndex].has(candidate));
      if (candidates.length === 0) {
        if (dfsIndex === 0 ){
          throw Error("Invalid suduko problem");
        }

        this.pathRecord[dfsIndex].clear();
        dfsIndex--;
        this.ans[this.emptyHole[dfsIndex][0]][this.emptyHole[dfsIndex][1]] = 0;
        continue;
      }

      this.pathRecord[dfsIndex].add(candidates[0]);
      this.ans[this.emptyHole[dfsIndex][0]][this.emptyHole[dfsIndex][1]] = candidates[0];
      dfsIndex++;
    }

    for (let row  = 0; row < this.GRID_SIZE; row ++) {
      for (let col = 0; col < this.GRID_SIZE; col ++) {
        if (this.grid[row][col] !== 0) {
          this.ans[row][col] = this.grid[row][col];
        }
      }
    }
    return this.ans;
  }


}