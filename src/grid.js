export class Grid {

    /**
     *
     * @param grid {Number [][]}
     * @param GRID_SIZE {Number}
     * @param BOX_SIZE {Number}
     */
    constructor(grid, GRID_SIZE, BOX_SIZE) {
        this._check(grid, GRID_SIZE, BOX_SIZE);
        this.BOX_SIZE = BOX_SIZE
        this.GRID_SIZE = GRID_SIZE
        this.grid = grid
    }

    /**
     *
     * @param grid {Number [][]}
     * @param GRID_SIZE {Number}
     * @param BOX_SIZE {Number}
     * @private
     */
    _check(grid, GRID_SIZE, BOX_SIZE) {
        if (!grid || grid.length !== GRID_SIZE ||
            GRID_SIZE !== BOX_SIZE **2 ||
            grid.some(row => row.length !== GRID_SIZE ) ||
            grid.length !== GRID_SIZE) {
            throw new Error('Invalid grid');
        }
    }
}

