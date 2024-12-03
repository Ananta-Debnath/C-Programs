#include <stdio.h>
#include <math.h>

/*
Remaining:
    Promotion
    Checkmate
*/

char board[9][9];
int king[2][2];
int castle_valid[2][2];
int move_ls[200][5];
int move_no, m, check, checkmate, checking, castling;
int (*move_piece[6])(int, int, int, int, int);

// Extra Declaration
int check_for_check();
int check_for_checkmate();

// Functions
int initialize_board()
{
    move_no = 1;
    m = -1;
    checking = 0;
    board[0][0] = ' ';
    for(int i=0; i<2; i++){
        king[i][0] = 5;
        king[i][1] = (i*7) + 1;
        for(int j=0; j<2; j++) castle_valid[i][j] = 1;
    }
    char pieces[8] = "RNBQKBNR";
    for(int i=0; i<8; i++){
        board[i+1][0] = 'A' + i;
        board[0][i+1] = '1' + i;
        board[i+1][2] = 'P';
        board[i+1][7] = 'p';
        board[i+1][1] = pieces[i];
        board[i+1][8] = pieces[i] + 32;
        for(int j=3; j<7; j++) board[i+1][j] = ' ';
    }
    return 0;
}

int show_board()
{
    printf("\nMove no: %d\n\n", move_no-1);
    for(int i=8; i>=0; i--){
        printf("------------------------------------\n");
        for(int j=0; j<9; j++){
            printf(" %c |", board[j][i]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int write_on_screen(int k)
{
    if(k == 2){
        printf("More than 1 move found!\n");
    }
    else if(check != 0){
        printf("Check!\n");
    }
    else if(k == 0){
        printf("Invalid move!\n");
    }
    else if(k == -1){
        printf("Syntax Error!\n");
    }
}

int undo_move()
{
    m *= -1;
    int x1 = move_ls[move_no-2][0];
    int y1 = move_ls[move_no-2][1];
    int x2 = move_ls[move_no-2][2];
    int y2 = move_ls[move_no-2][3];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = move_ls[move_no-2][4];
}

int move(int x1, int y1, int x2, int y2)
{
    move_ls[move_no-1][0] = x1;
    move_ls[move_no-1][1] = y1;
    move_ls[move_no-1][2] = x2;
    move_ls[move_no-1][3] = y2;
    move_ls[move_no-1][4] = board[x2][y2];

    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';
    move_no++;

    if(check_for_check()){
        m *= -1;
        undo_move();
        return 0;
    }

    int y[2] = {1, 8};
    if(y1 == y[(m+1)/2]) // Castle Validity
    {
        int i = (m+1)/2;
        if(x1 == 1) castle_valid[i][0] = 0;
        else if(x1 == 8) castle_valid[i][1] = 0;
    }

    m *= -1;
    check = check_for_check();
    // printf("\nMove no: %d\n\n", move_no);
    if(castling == 0) show_board();
    return 1;
}

int move_pawn(int x, int y, int x0, int y0, int q)
{
    char p = 'P' + (16*(m+1));
    int t[2] = {8,1};
    if(y == t[(m+1)/2] && checking != 1){ // Promotion
        if(q == 'Q' || q == 'R' || q == 'N' || q == 'B') q = q + (16*(m+1));
        else return -1;
    }
    else q = p;

    if(x0 == 0)
    {
        if(board[x][y] == ' ' && checking != 1)
        {
            if(board[x][y+m] == p){
                board[x][y+m] = q;
                return move(x, y+m, x, y);
            }

            if(y-4 == (m+1)/2 && board[x][y+(2*m)] == p){
                return move(x, y+(2*m), x, y);
            }
        }
        else
        {
            int v=0, d=0;
            if(board[x+1][y+m] == p){
                d = 1;
                v += 1;
            }
            if(board[x-1][y+m] == p){
                d = -1;
                v += 1;
            }

            if(v == 2) return 2;
            if(v == 1){
                int k = 1;
                if(!checking) k = move(x+d, y+m, x, y);
                return k;
            }
        }
    }
    else
    {
        if(abs(x-x0) == 1 && board[x0][y+m] == p){
            board[x0][y+m] = q;
            return move(x0, y+m, x, y);
        }
    }
    return 0;
}

int move_bishop_rook_queen(int x, int y, int l, int a[], int b[], char p)
{
    int v[9] = {0};
    int x0, y0;
    for(int i=0; i<l; i++){
        int d = 0;
        do{
            d++;
            x0 = x+(a[i]*d);
            y0 = y+(b[i]*d);
            if(board[x0][y0] == p && x0<9 && x0>0 && y0<9 && y0>0){
                v[i] = d;
                v[l]++;
                break;
            }
        }while(board[x+(a[i]*d)][y+(b[i]*d)] == ' ');
        if(v[l] == 2) return 2;
    }
    if(v[l] == 1){
        if(checking == 1) return 1;
        for(int i=0; i<l; i++){
            if(v[i] != 0){
                return move(x+(a[i]*v[i]), y+(b[i]*v[i]), x, y);
            }
        }
    }
    else return 0;
}

int move_knight_king(int x, int y, int l, int a[][2], char p)
{
    int v=0, d=0;
    int x0, y0;
    for(int i=0; i<l; i++){
        x0 = x+a[i][0];
        y0 = y+a[i][1];
        if(board[x0][y0] == p && x0<9 && x0>0 && y0<9 && y0>0){
            v++;
            d = i;
        }
        if(v == 2) return 2;
    }
    if(v == 1){
        int k = 1;
        if(checking != 1) k = move(x+a[d][0], y+a[d][1], x, y);
        return k;
    }
    return 0;
}

int move_rook(int x, int y, int x0, int y0, int q)
{
    char p = 'R' + (16*(m+1)) - q;
    
    if(x0 == 0 && y0 == 0)
    {
        int a[] = {0, 0, 1, -1};
        int b[] = {1, -1, 0, 0};
        int k = move_bishop_rook_queen(x, y, 4, a, b, p);
        return k;
    }
    else if(y0 == 0){
        if(x0 == x){
            int v=0, d;
            for(int i = 1; i<9; i++)
            {
                if(board[x][i] == p){
                    d = i;
                    v++;
                }
            }
            if(v > 1) return 2;
            else if(v == 1){
                return move_piece[1](x, y, 0, d, q);
            }
            else return 0;
        }
        else if(board[x0][y] == p)
        {
            int a = (x-x0)/abs(x-x0);
            int d = 1;
            while(x0+(d*a) != x){
                if(board[x0+(d*a)][y] != ' ') return 0;
                d++;
            }
            if(q == 1) return 1;
            move(x0, y, x, y);
            return 1;
        }
        else return 0;
    }
    else if(x0 == 0 && board[x][y0] == p){
        int a = (y-y0)/abs(y-y0);
        int d = 1;
        while(y0+(d*a) != y){
            if(board[x][y0+(d*a)] != ' ') return 0;
            d++;
        }
        if(q == 1) return 1;
        move(x, y0, x, y);
        return 1;
    }
    return 0;
}

int move_bishop(int x, int y, int x0, int y0, int q)
{
    char p = 'B' + (16*(m+1)) + (15*q);
    
    if(x0 == 0 && y0 == 0)
    {
        int a[] = {1, 1, -1, -1};
        int b[] = {1, -1, -1, 1};
        int k = move_bishop_rook_queen(x, y, 4, a, b, p);
        return k;
    }
    else if(y0 == 0){
        int v = 0;
        int a = (x-x0)/abs(x-x0);
        int d = x-x0;
        if(board[x0][y+d] == p){
            v++;
            while(d-a){
                d -= a;
                if(board[x-d][y+d] != ' '){
                    v--;
                    break;
                }
            }
        }
        d = x-x0;
        if(board[x0][y-d] == p){
            v--;
            while(d-a){
                d -= a;
                if(board[x-d][y-d] != ' '){
                    v++;
                    break;
                }
            }
        }
        if(q == 1) return v;
        if(v == 0) return 2;
        else{
            d = x-x0;
            move(x0, y+(d*v), x, y);
            return 1;
        }
        return 0;
    }
    else if(x0 == 0){
        int v = 0;
        int a = (y-y0)/abs(y-y0);
        int d = y-y0;
        if(board[x+d][y0] == p){
            v++;
            while(d-a){
                d -= a;
                if(board[x+d][y-d] != ' '){
                    v--;
                    break;
                }
            }
        }
        d = y-y0;
        if(board[x-d][y0] == p){
            v--;
            while(d-a){
                d -= a;
                if(board[x-d][y-d] != ' '){
                    v++;
                    break;
                }
            }
        }
        if(q == 1) return v;
        if(v == 0) return 2;
        else{
            d = y-y0;
            move(x+(d*v), y0, x, y);
            return 1;
        }
        return 0;
    }
    return 0;
}

int move_queen(int x, int y, int x0, int y0, int q)
{
    char p = 'Q' + (16*(m+1));
    
    if(x0 == 0 && y0 == 0)
    {
        int a[] = {0, 0, 1, -1, 1, 1, -1, -1};
        int b[] = {1, -1, 0, 0, 1, -1, -1, 1};
        int k = move_bishop_rook_queen(x, y, 8, a, b, p);
        return k;
    }
    else
    {
        int v = 0;
        int r = move_piece[1](x, y, x0, y0, 1);
        if(r == 1) v++;
        int b = move_piece[3](x, y, x0, y0, 1);
        if(b != 0) v++;
        if(v == 2) return 2;

        if(r == 1 && x0 == 0) move(x, y0, x, y);
        else if(r == 1 && y0 == 0) move(x0, y, x, y);
        else if(b != 0 && x0 == 0) move(x+(b*(y-y0)), y0, x, y);
        else if(b != 0 && y0 == 0) move(x0, y+(b*(x-x0)), x, y);
        else return 1;
    }
}

int move_knight(int x, int y, int x0, int y0, int q)
{
    char p = 'N' + (16*(m+1));
    
    if(x0 == 0 && y0 == 0)
    {
        int a[8][2] = {{2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1}};
        return move_knight_king(x, y, 8, a, p);
    }
    else if(y0 == 0)
    {
        int b = x0-x;
        if(b>2 || b<-2 || b==0) return 1;
        int a[2][2] = {{b, 3-abs(b)}, {b, -3+abs(b)}};
        return move_knight_king(x, y, 2, a, p);
    }
    else if(x0 == 0)
    {
        int b = y0-y;
        if(b>2 || b<-2) return 1;
        int a[2][2] = {{3-abs(b), b}, {-3+abs(b), b}};
        return move_knight_king(x, y, 2, a, p);
    }
    else return 1;
}

int move_king(int x, int y, int x0, int y0, int q)
{
    char p = 'K' + (16*(m+1));
    int a[8][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    int i = (m+1)/2;
    x0 = king[i][0];
    y0 = king[i][1];
    if(!checking){
        king[i][0] = x;
        king[i][1] = y;
    }
    int k = move_knight_king(x, y, 8, a, p);
    if(k == 1 && !checking){
        castle_valid[i][0] = 0;
        castle_valid[i][1] = 0;
    }
    else{
        king[i][0] = x0;
        king[i][1] = y0;
    }
    return k;
}

int castle(int d)
{
    castling = 1;
    int a = (m+1)/2;
    int y[2] = {1, 8};
    int k = move_piece[1](king[a][0]+d, y[a], 0, 0, 0);
    if(k == 1){
        m *= -1;
        for(int i = 0; i < 2; i++){
            king[a][0] += d;
            k = check_for_check();
            if(k != 0){
                castling = 0;
                m *= -1;
                king[a][0] = 5;
                undo_move();
                return 0;
            }
        }
        m *= -1;
        castling = 0;
        board[king[a][0]][y[a]] = board[5][y[a]];
        board[5][y[a]] = ' ';
        castle_valid[a][0] = 0;
        castle_valid[a][1] = 0;
        show_board();
        return 5;
    }
    castling = 0;
    return 0;
}

int check_for_checkmate()
{
    checking = 2;
    for(int i=0; i<6; i++){
        for(int x=1; x<9; x++){
            for(int y=1; y<9; y++){
                if(move_piece[i](x, y, 0, 0, 0)){
                    undo_move();
                    checking = 0;
                    return 0;
                }
            }
        }
    }
    return 1;
}

int check_for_check()
{
    checking++;
    int x = king[(m+1)/2][0];
    int y = king[(m+1)/2][1];
    int k = 0;
    m *= -1;
    for(int i=0; i<6; i++){
        k += move_piece[i](x, y, 0, 0, 0);
        if(k>0) break;
    }
    m *= -1;
    checking--;
    return k;
}

int figure_position(char in[], int pos[5])
{
    if(in[2] != '\n')
    {
        if(in[0]>='a' && in[0]<='h'){
            pos[2] = in[0] - 'a' + 1;
        }
        else if(in[0]>='1' && in[0]<='8'){
            pos[3] = in[0] - '0';
        }
        else if(in[0] == 'x'){
        }
        else return 0;

        return figure_position(&in[1], pos);
    }
    else
    {
        if(in[0]<'a' || in[0]>'h' || in[1]<'1' || in[1]>'8') return 0;

        pos[0] = in[0] - 'a' + 1;
        pos[1] = in[1] - '0';
        return 1;
    }
}

int take_input()
{
    char color[2][6] = {"White", "Black"};
    char input[6] = {0};
    int p, d;
    int pos[5] = {0};

    d = (m+1)/2;
    printf("%s's move: ", color[d]);
    fgets(input, 7, stdin);
    if(input[0] <= 'h' && input[0] >= 'a'){ // Pawn
        p = 0;
        d = 0;
        for(int i = 2; i < 5; i++){
            if(input[i] == '='){
                input[i] = '\n';
                pos[4] = input[i+1];
                break;
            }
        }
    }
    else if(input[0] == 'O'){ // Castle
        p = 0;
        if(input[2] == 'O'){
            if(input[4] == 'O'){
                if(castle_valid[d][0] == 1){
                    p = castle(-1);
                }
            }
            else if(castle_valid[d][1] == 1){
                p = castle(1);
            }
        }
        return p;
    }
    else
    {
        d = 1;
        switch (input[0])
        {
        case 'R':
            p = 1;
            break;
        case 'N':
            p = 2;
            break;
        case 'B':
            p = 3;
            break;
        case 'Q':
            p = 4;
            break;
        case 'K':
            p = 5;
            break;
        case 'u':
            p = -4;
            break;
        case 'r':
            p = -3;
            break;
        case 'q':
            p = -2;
            break;
        default:
            p = -1;
            break;
        }
    }
    if(p < 0) return p;

    char a = 'A' + (16*(m+1));
    if(figure_position(&input[d], pos) != 0){
        if(board[pos[0]][pos[1]]<a || board[pos[0]][pos[1]]>(a+25)){
            return move_piece[p](pos[0], pos[1], pos[2], pos[3], pos[4]);
        }
    }
    return -1;
}

int main()
{
    // Set Move Function Pointer
    move_piece[0] = move_pawn;
    move_piece[1] = move_rook;
    move_piece[2] = move_knight;
    move_piece[3] = move_bishop;
    move_piece[4] = move_queen;
    move_piece[5] = move_king;

    int quit = 0;
    while(quit == 0)
    {
        initialize_board();
        show_board();
        int k;
        char Y;
        while(1)
        {
            k = take_input();
            if(k == -2)
            {
                printf("Quit? : ");
                scanf("%c", &Y);
                if(Y == 'y' || Y == 'Y'){
                    quit = 1;
                    break;
                }
            }
            else if(k == -3)
            {
                printf("Restart? : ");
                scanf("%c", &Y);
                if(Y == 'y' || Y == 'Y') break;
            }
            else if(k == -4){
                undo_move();
                move_no--;
                show_board();
            }
            else{
                write_on_screen(k);
            }
        }
    }

    return 0;
}