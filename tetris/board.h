class Board{

    private:
        int board[200][200];
        int item[5][3];
        int height, width;
        
    public:

        bool canMove;

        int getHeight(){
            return height;
        }
        
        int getWidth(){
            return width;
        }

        Board(int height, int width){

            this->height = height;
            this->width = width;

            for(int i=0; i< 200; i++)
                for(int j=0; j<200; j++)
                    board[i][j] = 0;

            canMove = false;

        }

        void addItem(int item[5][3]) {
            // adds item to the board
            // by setting boards item to the given ref.
            for(int i=0; i<5; i++){
                for(int j=0; j<3; j++){
                    this->item[i][j] = item[i][j];
                }
            }
            canMove = true;
        }

        void fixItem(){

            // fix this->item to board
            // by assigning the values

            int x, y;
            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                board[x][y] = item[i][2];

            }

            for(int i=0; i<5; i++){
                item[i][0] = 0;
                item[i][1] = 0;
                item[i][2] = 0;
            }

            canMove = false;

            move(14, 80);
            printw("need to add item");

        }

        bool drop() {

            int x, y, solid;

            for(int i=0; i<5; i++){
                move(8+i, 80);
                printw("[%d %d %d]", item[i][0], item[0][1], item[0][2]);
            }

            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                solid = item[i][2];

                if(!solid)
                    continue;

                if(y >= height-1 || board[x][y+1] == 1){
                    fixItem();
                    canMove = false;
                    return false;
                }
            }

            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                solid = item[i][2];

                if(!solid)
                    continue;

                if(y < height-1 && board[x][y+1] == 0){
                    item[i][0] = x;
                    item[i][1] = y+1;
                }
            }
        
            return true;
        }

        void moveLeft(){

            move(15, 80);
            printw("last called : moveLeft ");

            int x, y, solid;

            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                solid = item[i][2];

                if(!solid)
                    continue;

                if(x-1 < 0 || board[y][x-1] != 0){
                    return;
                }

            }

            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                solid = item[i][2];

                if(!solid)
                    continue;


                move(16+i, 80);
                printw("move left possible  : %d", x-1 >= 0);

                if(x-1 >= 0 && board[y][x-1] == 0){
                    item[i][0] = x-1;
                    item[i][1] = y;
                }
                else {
                    return;
                }

            }
 
        }

        void moveRight(){

            move(15, 80);
            printw("last called : moveRight");

            int x, y, solid;

            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                solid = item[i][2];

                if(!solid)
                    continue;

                move(16+i, 80);
                printw("move right possible : %d %d - %d", x+1, width, (x+1 >= width));

                if(x+1 >= width || board[y][x+1] != 0){
                    return;
                }

            }

            for(int i=0; i<5; i++){

                x = item[i][0];
                y = item[i][1];
                solid = item[i][2];

                if(!solid)
                    continue;

                if(board[y][x+1] == 0){
                    item[i][0] = x+1;
                    item[i][1] = y;
                }

            }
 
        }

        void draw() {
            drawPanel();
            drawBoard();
            drawItem();
            refresh();
        }

        void drawPanel() {
            for(int i=0; i <= width; i++){
                move(0, i);
                printw(" ");
                move(height+1, i);
                printw(" ");
            }

            for(int i=1; i < height; i++) {
                move(i, 0);
                printw("#");
                move(i, width);
                printw("#");
            }
        }

        void drawItem() {

            int x, y;

            for(int i=0; i<5; i++){
                x = item[i][0];
                y = item[i][1];

                if(item[i][2] == 1){
                    move(y, x);
                    printw("X");
                }
            }

        }

        void drawBoard(){

            for(int i=0; i<height; i++) {

                for(int j=0; j<width; j++) {

                    move(j+1, i);

                    if(board[i][j] != 0){
                        printw("X");
                    }
                    else {
                        printw(" ");
                    }

                    move(j+1, width);
                    printw("| %d ", j+1);   
                    
                }
            }

        }

        void fill(){
            for(int i=0; i< width; i++){
                board[i][height-2] = 1;
            }
        }

        bool clearGround(){

            bool clear = false;
            
            for(int i=height; i >= 0; i--){

                clear = true;

                for(int j=0; j<width-1; j++){
                    if(board[j][i] == 0)
                        clear = false;
                }
                move(i, width+5);
                printw("%d", clear);

                if(clear){
                    for(int j=0; j<width; j++){
                        board[j][i] = 0;
                    }

                    // pull down
                    for(int k=i; k > 0; k--){
                        for(int j=0; j<width; j++){
                            board[j][k] = board[j][k-1];
                        }
                    }

                    for(int j=0; j<width; j++){
                        board[j][0] = 0;
                    }

                }

            }

            return false;

        }


};
