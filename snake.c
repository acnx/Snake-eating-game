#include<stdio.h>
#include<time.h>
#include<string.h>
int ROW = 20;//围墙
int LINE = 50;
//定义蛇头的坐标
int head_x = 0;
int head_y = 0;
int snake_length = 5;//定义蛇的长度
int head_v = 5;//定义初始数据：蛇的长度
//定义蛇尾坐标
int tail_x = 0;
int tail_y = 0;
int count = 0;//统计实物个数
int ch,sh;//方向键键值
//食物坐标
int  food_x = 0;
int  food_y = 0;
int main(){//主函数
    char map[ROW][LINE]; //定义地图：map
    memset(map,0,sizeof(map));
    /* memset---将map中当前位置后面的（）个字节用0代替并返回map
     * sizeof---返回map对象所占的内存字节数
     */
    createMap(map);   //创建地图
    //初始化蛇的信息：蛇头在地图中间
    head_x = ROW/2;
    head_y = LINE/2;

    int snake[ROW][LINE];
    memset(snake,0,sizeof(snake));
    //将snake数组中当前位置后面的（）个字节用0代替并返回snake

    createSnake(snake); //创建蛇

    createFood(map,snake);//创建食物

    showMapAndSnake(map,snake);//同时打印蛇与地图
    //蛇的运动
    run(map,snake);

    result();

    return 0;
}
//-创建地图
void createMap(char map[ROW][LINE]){
    //上下
    for(int i=0;i<LINE;i++){
        map[0][i] = '#';            //【0】【i】为第一行的的坐标
        map[ROW-1][i] = '#';        //【ROW】【i】为最后行的坐标
    }
    //

    //左右
    for(int i=0;i<ROW;i++){
        map[i][0] = '#';
        map[i][LINE-1] = '#';
    }

}

//创建蛇
void createSnake(int snake[ROW][LINE]){
    //蛇头的坐标与内容
    int value = snake_length;
    snake[head_x][head_y] = value;


    //蛇身设置
    for(int i=0;i<snake_length;i++){
        snake[head_x][head_y+1+i] = --value;
    }

    //获得蛇尾的坐标
    tail_x = head_x;
    tail_y = head_y + snake_length-1;

}
//地图与蛇 同时打印
void showMapAndSnake(char map[ROW][LINE],int snake[ROW][LINE]){
    for(int i=0;i<ROW;i++){
        for(int j=0;j<LINE;j++){
            if(snake[i][j]!=0){
                if(snake[i][j]==head_v){
                    printf("@");
                }else{
                    printf("a");
                }
            }else{
                printf("%c",map[i][j]);
            }
        }
        printf("\n");
    }
}
//创建食物
void createFood(char map[ROW][LINE],int snake[ROW][LINE]){
    int  food_x = 0;
    int food_y = 0;
    srand((unsigned)time(NULL));
    while(map[food_x][food_y]=='#'||snake[food_x][food_y]!=0){
        // srand
        food_x = rand()%ROW+1;
        food_y = rand()%LINE+1;

        //srand - 初始化随机种子
        //rand  - 产生随机数
    }
    map[food_x][food_y] = 'O';


}

//蛇尾
void moveTail(int snake[ROW][LINE]){
    if(snake[head_x][head_y]!='O'){
        //-上
        if(snake[tail_x][tail_y]+1 == snake[tail_x-1][tail_y]){
            snake[tail_x][tail_y] = 0;
            tail_x--;
        }
        //如果蛇尾[tail_x][tail_y]的前一个snake[tail_x][tail_y]+1的坐标=蛇尾正上方的坐标
        //那么 给蛇尾赋值为0，即不打印这个坐标位置的蛇尾
        //-下
        else if(snake[tail_x][tail_y]+1==snake[tail_x+1][tail_y]){
            snake[tail_x][tail_y] = 0;
            tail_x++;
        }
        //-左
        else if(snake[tail_x][tail_y]+1==snake[tail_x][tail_y-1]){
            snake[tail_x][tail_y] = 0;
            tail_y--;
        }
        //-右
        else if(snake[tail_x][tail_y]+1==snake[tail_x][tail_y+1]){
            snake[tail_x][tail_y] = 0;
            tail_y++;
        }
    }
}
//蛇撞墙
int isWall()
{
    if(head_x==0||head_x==ROW-1||head_y==0||head_y==LINE-1)
    {
        return 0;
    }else{
        return 1;
    }
}
//吃食物
int eatFood(char map[ROW][LINE])
{
    if(map[head_x][head_y]=='O')
    {
        map[head_x][head_y] = 0;
        count++;
        return 1;

    }else{
        return 0;
    }
}
//结果处理
void result(){
    printf("Game Over!\n");
    printf("Your Score is:%d\n",count);
    printf("Please Enter\n");
}


// 蛇的移动
void run(char map[ROW][LINE],int snake[ROW][LINE]){
    //定义蛇的运动方向
    char direct;
    while(1){
        if(isWall()){
            //判断键盘是否被敲击
            if(kbhit()){
                // WASD控制方向
                //获得键盘某个键的信息w
                char ch = getch();
                if(ch==-32){
                    char sh=getch();
                    if(sh==72){
                        if(direct=='s'){
                            continue;
                        }
                        direct = 'w';

                    }else if(sh==80){
                        if(direct=='w'){
                            continue;
                        }
                        direct = 's';

                    }else if(sh==75){
                        if(direct=='d'){
                            continue;
                        }
                        direct = 'a';

                    }else if(sh==77){
                        if(direct=='a'){
                            continue;
                        }
                        direct = 'd';

                    }
                }else{
                    if(ch=='A'||ch=='a'){
                        if(direct=='d'){
                            continue;
                        }
                        direct = 'a';
                    }else if(ch=='D'||ch=='d'){
                        if(direct=='a'){
                            continue;
                        }
                        direct = 'd';
                    }else if(ch=='W'||ch=='w'){
                        if(direct=='s'){
                            continue;
                        }
                        direct = 'w';
                    }else if(ch=='S'||ch=='s'){
                        if(direct=='w'){
                            continue;
                        }
                        direct = 's';
                    }else{
                        continue;
                    }
                }

                //通过方向direct控制蛇的移动
                switch (direct) {
                case 'w':{// 上


                    // 判断移动之后，是否接触到蛇的身体

                    if(snake[head_x-1][head_y]!=0){
                        return;
                    }

                    // 确定蛇头的位置、将移动后的位置设置为蛇头的坐标
                    snake[head_x-1][head_y] = ++head_v;
                    head_x--;

                }break;
                case 's':{//下


                    if(snake[head_x+1][head_y]!=0){
                        return;
                    }


                    snake[head_x+1][head_y] = ++head_v;
                    head_x++;
                }break;
                case 'a':{//左



                    if(snake[head_x][head_y-1]!=0){
                        return;
                    }

                    snake[head_x][head_y-1] = ++head_v;
                    head_y--;

                }break;
                case 'd':{//右

                    if(snake[head_x][head_y+1]!=0){
                        return;
                    }

                    snake[head_x][head_y+1] = ++head_v;
                    head_y++;
                }break;
                default:
                    break;
                }
                // 创建完毕之后，进行蛇的绘制
                if(direct=='a'||direct=='w'||direct=='s'||direct=='d'){
                    //先将控制台清空
                    system("cls");

                    if(eatFood(map)){
                        createFood(map,snake);
                    }else{
                        //先将蛇尾处理
                        moveTail(snake);

                    }


                    //重新绘制
                    showMapAndSnake(map,snake);
                }
            }


        }else{
            return;
        }
    }


}


