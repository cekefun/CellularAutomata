void kernel ProcessMultiArray(global int* data, global int* target, int length){
    //LeftMost
    int nextTopLeft = 0;
    int nextLeft = 0;
    int nextBotLeft = 0;
    int nextTop = 0;
    if (get_global_id(0)!= 0){
        nextTop = data[(get_global_id(0)-1) * length];
    }
    int nextSelf = data[(get_global_id(0)) * length];
    int nextBot = 0;
    if (get_global_id(0)!= get_global_size(0)-1){
        nextBot = data[(get_global_id(0)+1) * length];
    }
    int neighbours = 0;
    size_t id;
    //all except the last one
    for(int i = 0; i < length - 1; i++){
        neighbours = 0;
        id = get_global_id(0) * length + i;
        neighbours += nextTopLeft + nextLeft + nextBotLeft + nextTop + nextBot;
        nextTopLeft = nextTop;
        nextLeft = nextSelf;
        nextBotLeft = nextBot;
        int self = nextSelf;

        nextSelf = data[(get_global_id(0)) * length + i+1];
        neighbours += nextSelf;

        if (get_global_id(0)!= 0){
            //TopRight
            nextTop = data[(get_global_id(0)-1) * length + i+1];
            neighbours += nextTop;
        }
        if(get_global_id(0) != get_global_size(0)-1){
            //BotLeft
            nextBot = data[(get_global_id(0)+1) * length + i+1];
            neighbours += nextBot;
        }

        if(self == 1 && neighbours < 2){
            target[id] = 0;
        }
        if(self == 1 && neighbours > 3){
            target[id] = 0;
        }
        if(self == 1 && neighbours >=2 && neighbours <= 3){
            target[id] = 1;
        }
        if(self == 0 && neighbours == 3){
            target[id] = 1;
        }
    }
    //Rightmost
    neighbours = nextTopLeft + nextLeft + nextBotLeft + nextTop + nextBot;
    id = get_global_id(0) * length + length -1;
    if(nextSelf == 1 && neighbours < 2){
        target[id] = 0;
    }
    if(nextSelf == 1 && neighbours > 3){
        target[id] = 0;
    }
    if(nextSelf == 1 && neighbours >=2 && neighbours <= 3){
        target[id] = 1;
    }
    if(nextSelf == 0 && neighbours == 3){
        target[id] = 1;
    }
}