//
// Created by yiran on 2021/7/1.
//
#include<vector>
#include<algorithm>

#ifndef CF_BASE_BLOCKEDLIST_H
#define CF_BASE_BLOCKEDLIST_H

#include "../../template/cp_template.h"

class BlockedList{
public:
    int block_size, list_size;
    std::vector<std::vector<int>> data;
    std::vector<int> block_add;
    std::vector<int> blockL, blockR;
    BlockedList() {
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>();
        blockL=std::vector<int>();
        blockR=std::vector<int>();
        block_size=0;
        list_size=0;
    }
    void CalculateBlockRange() {
        for(int i=0;i<=list_size/block_size;++i) {
            blockL.emplace_back(i*block_size);
            blockR.emplace_back(std::min((i+1)*block_size-1, list_size-1));
        }
    }
    BlockedList(int block_size, int list_size) {
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>();
        this->block_size=block_size;
        this->list_size = list_size;
        CalculateBlockRange();
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(blockR[i]-blockL[i]+1);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    BlockedList(int block_size, const std::vector<int> &list_data) {
        this->block_size=block_size;
        this->list_size=list_data.size();
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>(block_size);
        CalculateBlockRange();
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(list_data.begin()+blockL[i],
                                        list_data.begin() + blockR[i]+1);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    BlockedList(int block_size, int *list_data, int list_size) {
        this->block_size=block_size;
        this->list_size=list_size;
        data=std::vector<std::vector<int>>();
        block_add=std::vector<int>(block_size);
        CalculateBlockRange();
        for(int i=0;i<=list_size / block_size; ++i) {
            std::vector<int> data_block(list_data+blockL[i],
                                        list_data + blockR[i]+1);
            data.push_back(data_block);
            block_add.push_back(0);
        }
    }

    int GetIndex(int index) {
        return data[index / block_size][index % block_size] + block_add[index / block_size];
    }

    void AddIndex(int index, int v) {
        data[index / block_size][index % block_size] += v;
    }

    void SetIndex(int index, int v) {
        data[index / block_size][index % block_size] = v;
    }

    void AddRange(int l, int r, int v) {
        int lblock = l / block_size, rblock= r / block_size;
        if(lblock==rblock) {
            for(int i=l%block_size;i<r%block_size;++i)
                data[lblock][i]+=v;
            return;
        }

        for(int i=l%block_size; i<block_size; ++i) {
            data[lblock][i]+=v;
        }
        for(int i=0;i<=r%block_size; ++i) {
            data[rblock][i]+=v;
        }
        for(int i=lblock+1;i<rblock;++i) {
            block_add[i]+=v;
        }
    }
};

#endif //CF_BASE_BLOCKEDLIST_H
