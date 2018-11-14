void kernel ProcessMultiArray(global int* data, global int* target){
    size_t id = (get_global_id(1) * get_global_size(0)) + get_global_id(0);

    int neighbours = 0;

    if(get_global_id(0) !=0){
        neighbours += data[get_global_id(1) * get_global_size(0) + (get_global_id(0)-1)];
        if (get_global_id(1) != 0){
            neighbours += data[(get_global_id(1)-1) * get_global_size(0) + (get_global_id(0)-1)];
        }
        if (get_global_id(1) != get_global_size(1)-1){
            neighbours += data[(get_global_id(1)+1) * get_global_size(0) + (get_global_id(0)-1)];
        }
    }

    if(get_global_id(0) != get_global_size(0)-1){
        neighbours += data[get_global_id(1) * get_global_size(0) + (get_global_id(0)+1)];
        if (get_global_id(1) != 0){
            neighbours += data[(get_global_id(1)-1) * get_global_size(0) + (get_global_id(0)+1)];
        }
        if (get_global_id(1) != get_global_size(1)-1){
            neighbours += data[(get_global_id(1)+1) * get_global_size(0) + (get_global_id(0)+1)];
        }
    }

    if(get_global_id(1) != 0){
        neighbours += data[(get_global_id(1)-1) * get_global_size(0) + get_global_id(0)];
    }

    if(get_global_id(1) != get_global_size(1)-1){
        neighbours += data[(get_global_id(1)+1) * get_global_size(0) + get_global_id(0)];
    }

    int state = data[id];

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