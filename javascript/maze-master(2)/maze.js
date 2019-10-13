var ctx, wid, hei, cols, rows, maze, start = { x: -1, y: -1 }, end = { x: -1, y: -1 }, grid = 8, padding = 16, s, step;

function init() {
    createCanvas();
}
function createCanvas() {
    var canvas = document.createElement("canvas");
    wid = document.getElementById("maze").offsetWidth - padding;
    hei = 400;
    canvas.width = wid; canvas.height = 400;
    canvas.id = "canvas";
    ctx = canvas.getContext("2d");
    ctx.fillStyle = "gray"; ctx.fillRect(0, 0, wid, hei);
    var div = document.getElementById("maze")
    div.appendChild(canvas);
}
function onCreate() {
    var mazeType = document.getElementById("sltType").value;
    document.getElementById("btnCreateMaze").setAttribute("disabled", "disabled");
    var Ani = document.getElementById("chkAnimated").checked;
    if (Ani) {
        document.getElementById("canvas").setAttribute("disabled", "disabled");
        document.getElementById("skipButton").removeAttribute("disabled");
    }
    wid = document.getElementById("maze").offsetWidth - padding;
    hei = 400;
    cols = eval(document.getElementById("cols").value);
    rows = eval(document.getElementById("rows").value);
    if (mazeType == "Maze1") {
        cols = cols + 1 - cols % 2;//长宽为奇数
        rows = rows + 1 - rows % 2;
    }
    maze = createArray(cols, rows, 1); //初始为1,墙壁
    var canvas = document.getElementById("canvas");
    canvas.width = wid;
    canvas.height = hei;
    s = canvas.width / (grid * cols); //以宽对齐
    canvas.height = s * grid * rows;
    ctx.scale(s, s);
    end.x = end.y = -1;
    skipthis = false;
    document.getElementById("clearMaze").setAttribute("disabled", "disabled");
    if (mazeType == "Maze1") {
        start.x = Math.floor(Math.random() * (cols / 2));
        start.y = Math.floor(Math.random() * (rows / 2));
        if (!(start.x & 1)) start.x++; if (!(start.y & 1)) start.y++; //起始点设为奇数
        maze[start.x][start.y] = 0;
        depth = createArray(cols, rows, 0);
        parent = createArray(cols, rows, 0);
        dep = 0;
        if (Ani) {
            drawMaze();
            createMaze1();
        }
        else {
            createMaze1NonAni();
        }
    } else {
        start.x = start.y = 0;
        route = [];
        openList = [];
        closeList = [];
        density = document.getElementById("density").value / 100;
        density1 = document.getElementById("density1").value / 100;
        if (density > 1 || density < 0) {
            alert("invalid density1! Use default value 50");
            density = 0.5;
            document.getElementById("density").value = 50;//
        }
        if (density1 > 1 || density1 < 0) {
            alert("invalid density2! Use default value 90");
            density1 = 0.9;
            document.getElementById("density1").value = 90;//
        }
        findMap = createArray(cols, rows, -1);
        if (Ani) {
            drawMaze();
            createMaze2();
        }
        else {
            createMaze2NonAni();
        }
    }
}
function getCursorPos(event) {
    var rect = this.getBoundingClientRect();
    var x = Math.floor((event.clientX - rect.left) / grid / s),
        y = Math.floor((event.clientY - rect.top) / grid / s); 9
    var mazeType = document.getElementById("sltType").value;
    var Ani = document.getElementById("chkAnimated").checked;
    if (maze[x][y] == 1) return;
    if (start.x == -1) {
        start = { x: x, y: y };
        maze[start.x][start.y] = (maze[start.x][start.y] == 0) ? 3 : 8;
        drawBlock(start.x, start.y, maze[start.x][start.y]);
    } else if (end.x == -1) {
        end = { x: x, y: y };
        maze[end.x][end.y] = (maze[end.x][end.y] == 0) ? 3 : 8;
        drawBlock(end.x, end.y, maze[end.x][end.y]);
        if (Ani) {
            document.getElementById("canvas").setAttribute("disabled", "disabled");
            document.getElementById("skipButton").removeAttribute("disabled");
        }
        skipthis = false;
        step = 0;
        if (mazeType == 'Maze1') {
            if (Ani) solveMaze1();
            else solveMaze1NonAni();
        } else {
            if (Ani) solveMaze2();
            else solveMaze2NonAni();
        }
    }
}
function drawMaze() {
    for (var i = 0; i < cols; i++) {
        for (var j = 0; j < rows; j++) {
            switch (maze[i][j]) {
                case 0: ctx.fillStyle = "gray"; break;
                case 1: ctx.fillStyle = "black"; break;
                case 2: ctx.fillStyle = "red"; break;
                case 3: ctx.fillStyle = "yellow"; break;
                case 4: ctx.fillStyle = "#500000"; break;
                case 5: ctx.fillStyle = "blue"; break;
                case 6: ctx.fillStyle = "green"; break;
                case 7: ctx.fillStyle = "#005000"; break;
                case 8: ctx.fillStyle = "orange"; break;
            }
            ctx.fillRect(grid * i, grid * j, grid, grid);
        }
    }
}
function drawBlock(sx, sy, a) {
    switch (a) {
        case 0: ctx.fillStyle = "gray"; break;
        case 1: ctx.fillStyle = "black"; break;
        case 2: ctx.fillStyle = "red"; break;
        case 3: ctx.fillStyle = "yellow"; break;
        case 4: ctx.fillStyle = "#500000"; break;
        case 5: ctx.fillStyle = "blue"; break;
        case 6: ctx.fillStyle = "green"; break;
        case 7: ctx.fillStyle = "#005000"; break;
        case 8: ctx.fillStyle = "orange"; break;
    }
    ctx.fillRect(grid * sx, grid * sy, grid, grid);
}
function createArray(c, r, k) {
    var m = new Array(c);
    for (var i = 0; i < c; i++) {
        m[i] = new Array(r);
        for (var j = 0; j < r; j++) {
            m[i][j] = k;
        }
    }
    return m;
}
function setButton() {
    var mazeType = document.getElementById("sltType").value;
    if (mazeType == "Maze2") {
        document.getElementById("density").removeAttribute("disabled");
        document.getElementById("density1").removeAttribute("disabled");
        document.getElementById("wayOfGetG").removeAttribute("disabled");
    } else {
        document.getElementById("density").setAttribute("disabled", "disabled");
        document.getElementById("density1").setAttribute("disabled", "disabled");
        document.getElementById("wayOfGetG").setAttribute("disabled", "disabled");
    }
}
var skipthis = false;
function skip() {
    skipthis = true;
    document.getElementById("skipButton").setAttribute("disabled", "disabled");
}
function clearMaze() {
    var mazeType = document.getElementById("sltType").value;
    document.getElementById("clearMaze").setAttribute("disabled", "disabled");
    if (mazeType == "Maze1") clearMaze1();
    else clearMaze2();
}
function solveOK() {
    document.getElementById("clearMaze").removeAttribute("disabled");
    document.getElementById("footer").innerHTML = "step:" + step;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

var depth, parent, stack = [], dep, dDepth;
function createMaze1NonAni() {
    while (true) {
        var neighbours = getNeighbours1(start.x, start.y, 1), l;
        if (neighbours.length < 1) {
            stack.pop();
            if (stack.length < 1) {
                drawMaze(); stack = [];
                start.x = start.y = end.x = end.y = -1;
                document.getElementById("canvas").addEventListener("mousedown", getCursorPos, false);
                document.getElementById("btnCreateMaze").removeAttribute("disabled");
                document.getElementById("clearMaze").removeAttribute("disabled");
                return;
            }
            start = stack[stack.length - 1];
            dep -= 2;
        } else {
            var i = 2 * Math.floor(Math.random() * (neighbours.length / 2))
            l = neighbours[i];
            maze[l.x][l.y] = 0;
            var p = setParent(l);
            parent[l.x][l.y] = p;
            depth[l.x][l.y] = ++dep;
            l = neighbours[i + 1];
            maze[l.x][l.y] = 0;
            parent[l.x][l.y] = p;
            depth[l.x][l.y] = ++dep;
            start = l;
            stack.push(start);
        }
    }
}
function getNeighbours1(sx, sy, a) {
    var n = [];
    if (sx - 1 > 0 && maze[sx - 1][sy] == a && sx - 2 > 0 && maze[sx - 2][sy] == a) {
        n.push({ x: sx - 1, y: sy }); n.push({ x: sx - 2, y: sy });
    }
    if (sx + 1 < cols - 1 && maze[sx + 1][sy] == a && sx + 2 < cols - 1 && maze[sx + 2][sy] == a) {
        n.push({ x: sx + 1, y: sy }); n.push({ x: sx + 2, y: sy });
    }
    if (sy - 1 > 0 && maze[sx][sy - 1] == a && sy - 2 > 0 && maze[sx][sy - 2] == a) {
        n.push({ x: sx, y: sy - 1 }); n.push({ x: sx, y: sy - 2 });
    }
    if (sy + 1 < rows - 1 && maze[sx][sy + 1] == a && sy + 2 < rows - 1 && maze[sx][sy + 2] == a) {
        n.push({ x: sx, y: sy + 1 }); n.push({ x: sx, y: sy + 2 });
    }
    return n;
}
function getParent(node) {
    switch (parent[node.x][node.y]) {
        case 1: return { x: node.x, y: node.y + 1 };
        case 2: return { x: node.x + 1, y: node.y };
        case 3: return { x: node.x, y: node.y - 1 };
        case 4: return { x: node.x - 1, y: node.y };
    }
}
function setParent(l) {
    if (start.y == l.y + 1) return 1;
    if (start.x == l.x + 1) return 2;
    if (start.y == l.y - 1) return 3;
    if (start.x == l.x - 1) return 4;
}
function solveMaze1NonAni() {
    dDepth = depth[start.x][start.y] - depth[end.x][end.y];
    step = Math.abs(dDepth);
    if (dDepth < 0) {
        for (var i = 0; i < -dDepth; ++i) {
            maze[end.x][end.y] = 3;
            end = getParent(end);
        }
    } else {
        for (var i = 0; i < dDepth; ++i) {
            maze[start.x][start.y] = 3;
            start = getParent(start);
        }
    }
    while (true) {
        maze[start.x][start.y] = 2;
        if (start.x == end.x && start.y == end.y)
            break;
        start = getParent(start);
        ++step;
        maze[end.x][end.y] = 2;
        if (start.x == end.x && start.y == end.y)
            break;
        end = getParent(end);
        ++step;
    }
    drawMaze();
    solveOK();
}
function clearMaze1() {
    for (var i = 0; i < cols; ++i)
        for (var j = 0; j < rows; ++j)
            if (maze[i][j] != 1)
                maze[i][j] = 0;
    drawMaze();
    start.x = start.y = end.x = end.y = -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

var openList = [], closeList = [], sqrt2 = Math.sqrt(2), gType, density, density1, route = [];
function createMaze2NonAni() {
    for (; start.y < rows; start.y++) {
        for (; start.x < cols; start.x++) {
            maze[start.x][start.y] = Math.random() < density ? 0 : 1;
            if (maze[start.x][start.y] == 0)
                maze[start.x][start.y] = Math.random() < density1 ? 0 : 5;
            drawBlock(start.x, start.y, maze[start.x][start.y]);
        }
        start.x = 0;
    }
    document.getElementById("canvas").addEventListener("mousedown", getCursorPos, false);
    document.getElementById("btnCreateMaze").removeAttribute("disabled");
    start.x = start.y = end.x = end.y = -1;
    drawMaze();
}
function solveMaze2NonAni() {
    gType = getGType();
    if (!Astar()) {
        alert("no path!");
        refresh();
        clearMaze2();
        return
    }
    tmp = closeList[closeList.length - 1];
    while (tmp.par != -1) {
        var b = (closeList[tmp.par].x == 3) ? 1 : 2;
        if (closeList[tmp.par].x != tmp.x && closeList[tmp.par].y != tmp.y) step += b * sqrt2;
        else step += b;
        maze[tmp.x][tmp.y] = (maze[tmp.x][tmp.y] == 4) ? 3 : 8;
        route.push({ x: tmp.x, y: tmp.y });
        tmp = closeList[tmp.par];
    }
    refresh();
}
function Astar() {
    openList.push({ x: start.x, y: start.y, F: 0, G: Math.abs(end.x - start.x) + Math.abs(end.y - start.y), H: -1, par: -1 });
    openList[0].H = openList[0].F + openList[0].G;
    findMap[start.x][start.y] = 0;
    maze[end.x][end.y] = ([end.x][end.y] == 3) ? 0 : 5;
    while (openList.length != 0) {
        var tmp = popHeap(openList);
        closeList.push({ x: tmp.x, y: tmp.y, par: tmp.par });
        maze[tmp.x][tmp.y] = (maze[tmp.x][tmp.y] == 2) ? 4 : 7;
        if (tmp.x == end.x && tmp.y == end.y)
            return true;
        var neighbours = getNeighbours2(tmp.x, tmp.y);
        for (var i = 0; i < neighbours.length; ++i) {
            var cur = neighbours[i];
            var f = (cur.x != tmp.x && cur.y != tmp.y) ? tmp.F + sqrt2 : tmp.F + 1;
            switch (maze[cur.x][cur.y]) {
                case 0:
                    var g = getG(cur.x, cur.y);
                    pushHeap({ x: cur.x, y: cur.y, F: f, G: g, H: f + g, par: closeList.length - 1 });
                    maze[cur.x][cur.y] = 2; break;
                case 5:
                    var g = getG(cur.x, cur.y);
                    pushHeap({ x: cur.x, y: cur.y, F: 2 * f, G: g, H: f + g, par: closeList.length - 1 });
                    maze[cur.x][cur.y] = 6; break;
                case 2: case 6:
                    var pre = findHeap(cur.x, cur.y);
                    if (openList[pre].F > f) {
                        openList[pre].F = f;
                        openList[pre].H = openList[pre].F + openList[pre].G;
                        openList[pre].par = closeList.length - 1;
                        fixUp(pre); break;
                    }
            }
        }
    }
    return false;
}
function refresh() {
    maze[tmp.x][tmp.y] = (maze[tmp.x][tmp.y] == 4) ? 3 : 8;
    route.push({ x: tmp.x, y: tmp.y });
    for (var i = 0; i < closeList.length; ++i) {
        var cur = closeList[i];
        if (maze[cur.x][cur.y] == 4)
            maze[cur.x][cur.y] = 0;
        else if (maze[cur.x][cur.y] == 7)
            maze[cur.x][cur.y] = 5;
    }
    for (var i = 0; i < openList.length; ++i) {
        var cur = openList[i];
        if (maze[cur.x][cur.y] == 2)
            maze[cur.x][cur.y] = 0;
        else
            maze[cur.x][cur.y] = 5;
    }
    drawMaze();
    solveOK();
}
function getNeighbours2(sx, sy) {
    var n = [];
    if (sx > 0) {
        if (maze[sx - 1][sy] != 1 && maze[sx - 1][sy] != 4 && maze[sx - 1][sy] != 7)
            n.push({ x: sx - 1, y: sy });
        if (sy > 0 && maze[sx - 1][sy - 1] != 1 && maze[sx - 1][sy - 1] != 4 && maze[sx - 1][sy - 1] != 7)
            n.push({ x: sx - 1, y: sy - 1 });
        if (sy < rows - 1 && maze[sx - 1][sy + 1] != 1 && maze[sx - 1][sy + 1] != 4 && maze[sx - 1][sy + 1] != 7)
            n.push({ x: sx - 1, y: sy + 1 });
    }
    if (sx < cols - 1) {
        if (maze[sx + 1][sy] != 1 && maze[sx + 1][sy] != 4 && maze[sx + 1][sy] != 7)
            n.push({ x: sx + 1, y: sy });
        if (sy > 0 && maze[sx + 1][sy - 1] != 1 && maze[sx + 1][sy - 1] != 4 && maze[sx + 1][sy - 1] != 7)
            n.push({ x: sx + 1, y: sy - 1 });
        if (sy < rows - 1 && maze[sx + 1][sy + 1] != 1 && maze[sx + 1][sy + 1] != 4 && maze[sx + 1][sy + 1] != 7)
            n.push({ x: sx + 1, y: sy + 1 });
    }
    if (sy > 0 && maze[sx][sy - 1] != 1 && maze[sx][sy - 1] != 4 && maze[sx][sy - 1] != 7)
        n.push({ x: sx, y: sy - 1 });
    if (sy < rows - 1 && maze[sx][sy + 1] != 1 && maze[sx][sy + 1] != 4 && maze[sx][sy + 1] != 7)
        n.push({ x: sx, y: sy + 1 });
    return n;
}
function getGType() {
    switch (document.getElementById("wayOfGetG").value) {
        case "Manhattan": return 0;
        case "Euclidean": return 1;
        case "Chebyshev": return 2;
    }
}
function getG(x, y) {
    switch (gType) {
        case 0: return Math.abs(x - end.x) + Math.abs(y - end.y);
        case 1: return Math.sqrt((end.x - x) * (end.x - x) + (end.y - y) * (end.y - y));
        case 2:
            var longer = Math.abs(end.x - x), shorter = Math.abs(end.y - y);
            if (longer < shorter) { var tmp = longer; longer = shorter; shorter = tmp; }
            return shorter * sqrt2 + (longer - shorter);
    }
}
function clearMaze2() {
    for (var i = 0; i < route.length; ++i) {
        var cur = route[i];
        if (maze[cur.x][cur.y] == 3) {
            maze[cur.x][cur.y] = 0;
            drawBlock(cur.x, cur.y, 0);
        }
        else {
            maze[cur.x][cur.y] = 5;
            drawBlock(cur.x, cur.y, 5);
        }
    }
    route = [];
    openList = [];
    closeList = [];
    maze[start.x][start.y] = (maze[start.x][start.y] == 3) ? 0 : 5;
    maze[end.x][end.y] = (maze[end.x][end.y] == 3) ? 0 : 5;
    drawBlock(start.x, start.y, maze[start.x][start.y]);
    drawBlock(end.x, end.y, maze[end.x][end.y]);
    start.x = start.y = end.x = end.y = -1;
    return;
}
function popHeap() {
    var tmp = openList[0], l = openList.length - 1;
    findMap[openList[l].x][openList[l].y] = 0;;
    openList[0] = openList[l];
    openList.pop();
    pelocateDown(0);
    return tmp;
}
function pushHeap(obj) {
    openList.push(obj);
    var curN = openList.length - 1;
    findMap[obj.x][obj.y] = curN;
    fixUp(curN);
}
function findHeap(xx, yy) {
    return findMap[xx][yy];
}
function fixUp(curN) {
    if (curN == 0)
        return;
    var obj = openList[curN];
    var parN = Math.floor((curN - 1) / 2);
    for (; parN >= 0 && openList[parN].H > obj.H; curN = parN, parN = Math.floor((parN - 1) / 2)) {
        findMap[openList[parN].x][openList[parN].y] = curN;
        openList[curN] = openList[parN];
    }
    findMap[obj.x][obj.y] = curN;
    openList[curN] = obj;
}
function pelocateDown(n) {
    if (openList.length == 0)
        return;
    var child = 2 * n + 1, tmp = openList[n];
    for (; child < openList.length; n = child, child = 2 * n + 1) {
        if (child + 1 < openList.length && openList[child + 1].H < openList[child].H)++child;
        if (openList[child].H < tmp.H) {
            findMap[openList[child].x][openList[child].y] = n;
            openList[n] = openList[child];
        }
        else break;
    }
    findMap[tmp.x][tmp.y] = n;
    openList[n] = tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

function createMaze1() {
    if (skipthis) {
        createMaze1NonAni();
        return;
    }
    var neighbours = getNeighbours1(start.x, start.y, 1), l;
    if (neighbours.length < 1) {
        stack.pop();
        if (stack.length < 1) {
            stack = [];
            start.x = start.y = end.x = end.y = -1;
            document.getElementById("canvas").addEventListener("mousedown", getCursorPos, false);
            document.getElementById("btnCreateMaze").removeAttribute("disabled");
            return;
        }
        start = stack[stack.length - 1];
        dep -= 2;
    } else {
        var i = 2 * Math.floor(Math.random() * (neighbours.length / 2))
        l = neighbours[i];
        maze[l.x][l.y] = 0;
        var p = setParent(l);
        parent[l.x][l.y] = p;
        depth[l.x][l.y] = ++dep;
        drawBlock(l.x, l.y, 0);
        l = neighbours[i + 1];
        maze[l.x][l.y] = 0;
        parent[l.x][l.y] = p;
        depth[l.x][l.y] = ++dep;
        drawBlock(l.x, l.y, 0);
        start = l
        stack.push(start)
    }
    requestAnimationFrame(createMaze1);
}

function createMaze2() {
    if (skipthis) {
        createMaze2NonAni();
        return;
    }
    maze[start.x][start.y] = Math.random() < density ? 0 : 1;
    if (maze[start.x][start.y] == 0)
        maze[start.x][start.y] = Math.random() < density1 ? 0 : 5;
    drawBlock(start.x, start.y, maze[start.x][start.y]);
    if (start.x == (cols - 1) && start.y == (rows - 1)) {
        document.getElementById("btnCreateMaze").removeAttribute("disabled");
        document.getElementById("canvas").addEventListener("mousedown", getCursorPos, false);
        start.x = start.y = end.x = end.y = -1;
        return;
    }
    start.x = start.x + 1;
    if (start.x == cols) {
        start.x = 0;
        start.y = start.y + 1;
    }
    requestAnimationFrame(createMaze2);
}

function solveMaze1() {
    dDepth = depth[start.x][start.y] - depth[end.x][end.y];
    step = Math.abs(dDepth);
    requestAnimationFrame(toSameDepth);
}
function toSameDepth() {
    if (skipthis) {
        solveMaze1NonAni();
        return;
    }
    if (dDepth == 0)
        return requestAnimationFrame(LCA);
    if (dDepth < 0) {
        maze[end.x][end.y] = 3;
        drawBlock(end.x, end.y, 3);
        end = getParent(end);
        ++dDepth;
    } else {
        maze[start.x][start.y] = 3;
        drawBlock(start.x, start.y, 3);
        start = getParent(start);
        --dDepth;
    }
    requestAnimationFrame(toSameDepth);
}
function LCA() {
    if (skipthis) {
        solveMaze1NonAni();
        return;
    }
    maze[start.x][start.y] = 2;
    drawBlock(start.x, start.y, 2);
    if (start.x == end.x && start.y == end.y) {
        solveOK();
        return;
    }
    start = getParent(start);
    ++step;
    maze[end.x][end.y] = 2;
    drawBlock(end.x, end.y, 2);
    if (start.x == end.x && start.y == end.y) {
        solveOK();
        return;
    }
    end = getParent(end);
    ++step;
    requestAnimationFrame(LCA);
}

var tmp;
function solveMaze2() {
    gType = getGType();
    maze[end.x][end.y] = ([end.x][end.y] == 3) ? 0 : 5;
    openList.push({ x: start.x, y: start.y, F: 0, G: Math.abs(end.x - start.x) + Math.abs(end.y - start.y), H: -1, par: -1 });
    openList[0].H = openList[0].F + openList[0].G;
    findMap[start.x][start.y] = 0;
    requestAnimationFrame(AstarAni);
}
function AstarAni() {
    if (skipthis) {
        solveMaze2NonAni();
        return;
    }
    if (openList.length == 0) {
        alert("no path!");
        refresh();
        clearMaze2();
        return;
    }
    tmp = popHeap(openList);
    closeList.push({ x: tmp.x, y: tmp.y, par: tmp.par });
    maze[tmp.x][tmp.y] = (maze[tmp.x][tmp.y] == 2) ? 4 : 7;
    drawBlock(tmp.x, tmp.y, maze[tmp.x][tmp.y]);
    if (tmp.x == end.x && tmp.y == end.y) {
        tmp = closeList[closeList.length - 1];
        return requestAnimationFrame(traceBack);
    }
    var neighbours = getNeighbours2(tmp.x, tmp.y);
    for (var i = 0; i < neighbours.length; ++i) {
        var cur = neighbours[i];
        var f = (cur.x != tmp.x && cur.y != tmp.y) ? tmp.F + sqrt2 : tmp.F + 1;
        switch (maze[cur.x][cur.y]) {
            case 0:
                var g = getG(cur.x, cur.y);
                pushHeap({ x: cur.x, y: cur.y, F: f, G: g, H: f + g, par: closeList.length - 1 });
                maze[cur.x][cur.y] = 2;
                drawBlock(cur.x, cur.y, 2); break;
            case 5:
                var g = getG(cur.x, cur.y);
                pushHeap({ x: cur.x, y: cur.y, F: 2 * f, G: g, H: f + g, par: closeList.length - 1 });
                maze[cur.x][cur.y] = 6;
                drawBlock(cur.x, cur.y, 6); break;
            case 2: case 6:
                var pre = findHeap(cur.x, cur.y);
                if (openList[pre].F > f) {
                    openList[pre].F = f;
                    openList[pre].H = openList[pre].F + openList[pre].G;
                    openList[pre].par = closeList.length - 1;
                    fixUp(pre); break;
                }
        }
    }
    requestAnimationFrame(AstarAni);
}
function traceBack() {
    if (skipthis) {
        solveMaze2NonAni();
        return;
    }
    if (tmp.par == -1)
        return refresh();
    var b = (closeList[tmp.par].x == 3) ? 1 : 2;
    if (closeList[tmp.par].x != tmp.x && closeList[tmp.par].y != tmp.y) step += b * sqrt2;
    else step += b;
    maze[tmp.x][tmp.y] = (maze[tmp.x][tmp.y] == 4) ? 3 : 8;
    route.push({ x: tmp.x, y: tmp.y });
    drawBlock(tmp.x, tmp.y, maze[tmp.x][tmp.y]);
    tmp = closeList[tmp.par];
    requestAnimationFrame(traceBack);
}