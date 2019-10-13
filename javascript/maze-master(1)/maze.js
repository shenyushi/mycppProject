var ctx, wid, hei, cols, rows, maze, stack = [], start = { x: -1, y: -1 }, end = { x: -1, y: -1 }, grid = 8, padding = 16, s, density = 0.5;
/*function drawMaze() {
    for (var i = 0; i < cols; i++) {
        for (var j = 0; j < rows; j++) {
            switch (maze[i][j]) {
                case 0: ctx.fillStyle = "black"; break;
                case 1: ctx.fillStyle = "gray"; break;
                case 2: ctx.fillStyle = "red"; break;
                case 3: ctx.fillStyle = "yellow"; break;
                case 4: ctx.fillStyle = "#500000"; break;
            }
            ctx.fillRect(grid * i, grid * j, grid, grid);
        }
    }
}

function drawBlock(sx, sy, a) {
    switch (a) {
        case 0: ctx.fillStyle = "black"; break;
        case 1: ctx.fillStyle = "gray"; break;
        case 2: ctx.fillStyle = "red"; break;
        case 3: ctx.fillStyle = "yellow"; break;
        case 4: ctx.fillStyle = "#500000"; break;
    }
    ctx.fillRect(grid * sx, grid * sy, grid, grid);
}

function getFNeighbours(sx, sy, a) {
    var n = [];
    if (sx - 1 > 0 && maze[sx - 1][sy] == a) {
        n.push({ x: sx - 1, y: sy });
    }
    if (sx + 1 < cols - 1 && maze[sx + 1][sy] == a) {
        n.push({ x: sx + 1, y: sy });
    }
    if (sy - 1 > 0 && maze[sx][sy - 1] == a) {
        n.push({ x: sx, y: sy - 1 });
    }
    if (sy + 1 < rows - 1 && maze[sx][sy + 1] == a) {
        n.push({ x: sx, y: sy + 1 });
    }
    return n;
}
function solveMaze1() {
    if (start.x == end.x && start.y == end.y) {
        for (var i = 0; i < cols; i++) {
            for (var j = 0; j < rows; j++) {
                switch (maze[i][j]) {
                    case 2: maze[i][j] = 3; break; //正确路径变黄
                    case 4: maze[i][j] = 0; break; //错误路径清除
                }
            }
        }
        drawMaze();
        return;
    }
    var neighbours = getFNeighbours(start.x, start.y, 0);
    if (neighbours.length) {
        stack.push(start);
        start = neighbours[0];
        maze[start.x][start.y] = 2;
    } else {
        maze[start.x][start.y] = 4; //走错，退回
        start = stack.pop();
    }

    drawMaze();
    requestAnimationFrame(solveMaze1);
}
function getCursorPos(event) {
    var rect = this.getBoundingClientRect(); //整个地图的坐标
    var x = Math.floor((event.clientX - rect.left) / grid / s),
        y = Math.floor((event.clientY - rect.top) / grid / s);
    if (maze[x][y]) return; //点到墙壁
    if (start.x == -1) {
        start = { x: x, y: y };
    } else {
        end = { x: x, y: y };
        maze[start.x][start.y] = 2;
        solveMaze1();   //点到两个点
    }
}
function getNeighbours(sx, sy, a) {
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
}*/
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
var vs = [], depth = [], id = [];
var child, Amin；
function getChild(l) {
    if (start.y == l.y + 1)
        return 1;
    if (start.x == l.x + 1)
        return 2;
    if (start.y == l.y - 1)
        return 3;
    if (start.x == l.x - 1)
        return 4;
}
function createMaze1(dep) {
    var neighbours = getNeighbours(start.x, start.y, 1), l;
    if (neighbours.length < 1) {
        --dep;
        if (stack.length < 1) {
            drawMaze(); stack = [];
            start.x = start.y = -1; //初始化start
            document.getElementById("canvas").addEventListener("mousedown", getCursorPos, false); //冒泡阶段执行
            document.getElementById("btnCreateMaze").removeAttribute("disabled");
            RMQinit();
            return;
        }
        start = stack.pop();
    } else {
        var i = 2 * Math.floor(Math.random() * (neighbours.length / 2)) //随机偶数
        l = neighbours[i]; maze[l.x][l.y] = 0;
        var ch = getChild(l);
        child[start.x][start.y] = ch;
        child[l.x][l.y] = ch;
        vs.push({ x: l.x, y: l.y });
        depth.push(++dep);
        if (id[l.x][l.y] == -1) {
            id[l.x][l.y] = vs.length - 1;
        }
        l = neighbours[i + 1]; maze[l.x][l.y] = 0;
        vs.push({ x: l.x, y: l.y });
        depth.push(++dep);
        if (id[l.x][l.y] == -1) {
            id[l.x][l.y] = vs.length - 1;
        }
        start = l
        stack.push(start)
    }
    drawMaze();
    requestAnimationFrame(createMaze1(dep)); //动画
}
function RMQinit() {
    var c = id.length;
    var r = Math.ceil(Math.log(c) / Math.log(2) - 1);
    Amin = createArray(c, r, 0); //Amin[i][j]表示从id[i]开始，长度为2^(j+1)区间内的最大值
    for (var i = 0; i < c; ++i)
        Amin[i][0] = id[i];
    for (var j = 1; (1 << j) <= N; j++)
        for (var i = 1; i + (1 << j) - 1 <= N; i++)
            Amin[i - 1][j - 1] = min(Amin[i - 1][j - 2], Amin[i - 1 + (1 << (j - 1))][j - 2]);
}

function createMaze1NonAni() {
    while (true) {
        var neighbours = getNeighbours(start.x, start.y, 1), l;
        if (neighbours.length < 1) {
            if (stack.length < 1) {
                drawMaze(); stack = [];
                start.x = start.y = -1;
                document.getElementById("canvas").addEventListener("mousedown", getCursorPos, false); //点击时调用getCursorPos
                document.getElementById("btnCreateMaze").removeAttribute("disabled");  //create按钮可用
                return;
            }
            start = stack.pop(); //后退
        } else {
            var i = 2 * Math.floor(Math.random() * (neighbours.length / 2)) //随机偶数
            l = neighbours[i];
            maze[l.x][l.y] = 0; //0是墙壁
            l = neighbours[i + 1];
            maze[l.x][l.y] = 0;
            start = l
            stack.push(start)
        }
    }
}
function createMaze2() {

    var r = Math.random();

    maze[start.x][start.y] = r < density ? 0 : 1;

    drawMaze();

    if (start.x == (cols - 1) && start.y == (rows - 1)) {

        document.getElementById("btnCreateMaze").removeAttribute("disabled");
        return;
    }

    start.x = start.x + 1;
    if (start.x == cols) {
        start.x = 0;
        start.y = start.y + 1;
    }

    requestAnimationFrame(createMaze2);
}

function createMaze2NonAni() {

    for (var i = 0; i < cols; i++) {
        for (var j = 0; j < rows; j++) {
            maze[i][j] = Math.random() < density ? 0 : 1;

            drawBlock(i, j, maze[i][j]);
        }
    }
    document.getElementById("btnCreateMaze").removeAttribute("disabled");
}
*/
function createCanvas() {
    var canvas = document.createElement("canvas");
    wid = document.getElementById("maze").offsetWidth - padding;  //html 64行定义的
    hei = 400;

    canvas.width = wid; canvas.height = 400;
    canvas.id = "canvas";
    ctx = canvas.getContext("2d"); //ctx 为环境对象，通过ctx画图
    ctx.fillStyle = "gray"; ctx.fillRect(0, 0, wid, hei);
    var div = document.getElementById("maze")
    div.appendChild(canvas);
}

function init() {
    createCanvas();
}

function onCreate() {

    document.getElementById("btnCreateMaze").setAttribute("disabled", "disabled"); //设置时按钮不可用

    wid = document.getElementById("maze").offsetWidth - padding;
    hei = 400;

    cols = eval(document.getElementById("cols").value); //输入长宽
    rows = eval(document.getElementById("rows").value);

    var mazeType = document.getElementById("sltType").value; //maze 种类

    if (mazeType == "Maze1") {
        cols = cols + 1 - cols % 2; //奇数
        rows = rows + 1 - rows % 2;
        maze = createArray(cols, rows, 1);
        id = createArray(cols, rows, -1);
        child = createArray(cols, rows, 0); //0:nochild,1:down,2:right,3:up,4:left
    }

    var canvas = document.getElementById("canvas");
    canvas.width = wid;
    canvas.height = hei;
    s = canvas.width / (grid * cols); //占比
    canvas.height = s * grid * rows;

    ctx.scale(s, s); //占满屏幕


    if (mazeType == "Maze1") {

        start.x = Math.floor(Math.random() * (cols / 2));
        start.y = Math.floor(Math.random() * (rows / 2));
        if (!(start.x & 1)) start.x++; if (!(start.y & 1)) start.y++; //偶数变奇数，奇数是路
        maze[start.x][start.y] = 0;
        var dep = 0;
        if (document.getElementById("chkAnimated").checked) {
            vs.push({ x: start.x, y: start.y });
            depth.push(dep);
            id[start.x][start.y] = 0;
            createMaze1(dep);
        }
        else {
            createMaze1NonAni();
        }
    }
    else {

        start.x = 0;
        start.x = 0;

        if (document.getElementById("chkAnimated").checked) {

            createMaze2();
        }
        else {

            createMaze2NonAni();
        }
    }
}