typedef {{}} myType;

void kernel ProcessMultiArray(global myType* data, global myType* target, int length){
    //LeftMost
    myType nextTopLeft = 0;
    myType nextLeft = 0;
    myType nextBotLeft = 0;
    myType nextTop = 0;
    if (get_global_id(0)!= 0){
        nextTop = data[(get_global_id(0)-1) * length];
    }
    myType nextSelf = data[(get_global_id(0)) * length];
    myType nextBot = 0;
    if (get_global_id(0)!= get_global_size(0)-1){
        nextBot = data[(get_global_id(0)+1) * length];
    }
    myType neighbours = 0;
    size_t id;

    int topWeight = {{}};
    int topLeftWeight = {{}};
    int topRightWeight = {{}};
    int botWeight = {{}};
    int botLeftWeight = {{}};
    int botRightWeight = {{}};
    int leftWeight = {{}};
    int rightWeight = {{}};

//all except the last one
    for(int i = 0; i < length - 1; i++){
        neighbours = 0;
        id = get_global_id(0) * length + i;
        neighbours += topLeftWeight * nextTopLeft + leftWeight * nextLeft + botLeftWeight * nextBotLeft + topWeight * nextTop + botWeight * nextBot;
        nextTopLeft = nextTop;
        nextLeft = nextSelf;
        nextBotLeft = nextBot;
        myType self = nextSelf;

        //Right
        nextSelf = data[(get_global_id(0)) * length + i+1];
        neighbours += rightWeight * nextSelf;

        if (get_global_id(0)!= 0){
            //TopRight
            nextTop = data[(get_global_id(0)-1) * length + i+1];
            neighbours += topRightWeight * nextTop;
        }
        if(get_global_id(0) != get_global_size(0)-1){
            //BotLeft
            nextBot = data[(get_global_id(0)+1) * length + i+1];
            neighbours += botRightWeight * nextBot;
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
    neighbours = topLeftWeight * nextTopLeft + leftWeight * nextLeft + botLeftWeight * nextBotLeft + topWeight * nextTop + botWeight * nextBot;
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