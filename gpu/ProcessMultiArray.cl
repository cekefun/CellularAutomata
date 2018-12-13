typedef {{}} myType;

void kernel ProcessMultiArray(global myType* data, global myType* target){
    size_t id = (get_global_id(1) * get_global_size(0)) + get_global_id(0);

    myType neighbours = 0;

    if(get_global_id(0) !=0){
        //Top
        neighbours += {{}}*(data[get_global_id(1) * get_global_size(0) + (get_global_id(0)-1)]);
        if (get_global_id(1) != 0){
            //TopLeft
            neighbours += {{}}*(data[(get_global_id(1)-1) * get_global_size(0) + (get_global_id(0)-1)]);
        }
        if (get_global_id(1) != get_global_size(1)-1){
            //TopRight
            neighbours += {{}}*(data[(get_global_id(1)+1) * get_global_size(0) + (get_global_id(0)-1)]);
        }
    }

    if(get_global_id(0) != get_global_size(0)-1){
        //Bot
        neighbours += {{}}*(data[get_global_id(1) * get_global_size(0) + (get_global_id(0)+1)]);
        if (get_global_id(1) != 0){
            //BotLeft
            neighbours += {{}}*(data[(get_global_id(1)-1) * get_global_size(0) + (get_global_id(0)+1)]);
        }
        if (get_global_id(1) != get_global_size(1)-1){
            //BotRight
            neighbours += {{}}*(data[(get_global_id(1)+1) * get_global_size(0) + (get_global_id(0)+1)]);
        }
    }

    if(get_global_id(1) != 0){
        //Left
        neighbours += {{}}*(data[(get_global_id(1)-1) * get_global_size(0) + get_global_id(0)]);
    }

    if(get_global_id(1) != get_global_size(1)-1){
        //Right
        neighbours += {{}}*(data[(get_global_id(1)+1) * get_global_size(0) + get_global_id(0)]);
    }

    myType state = data[id];

    if(state == 1 && neighbours < 2){
        target[id] = 0;
    }
    if(state == 1 && neighbours > 3){
        target[id] = 0;
    }
    if(state == 1 && neighbours >=2 && neighbours <= 3){
        target[id] = 1;
    }
    if(state == 0 && neighbours == 3){
        target[id] = 1;
    }

}