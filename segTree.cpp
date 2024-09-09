#include <bits/stdc++.h>
#define ll long long
using namespace std;
class SegmentTree{
    vector<pair<int,int>>seg;
    vector<int>ans;
    int N;
    public:
    SegmentTree(int n,int val){
        N = n;
        seg.resize(4*n,{0,0});
        ans.resize(4*n , 0);
    }
    void Build(vector<int>&nums,int ind,int low, int high){
        if(low==high){
            if(nums[low] == 1){
                seg[ind] = {0,1};
            }
            else seg[ind] = {1,0};
            ans[ind] = 1;
            return;
        }
        int mid = (low+high)/2;
        Build(nums,2*ind+1,low,mid);
        Build(nums,2*ind+2,mid+1,high);
        int l = 2*ind + 1;
        int r = 2*ind + 2;

        auto x1 = seg[l];
        auto x2 = seg[r];
        if(x1.first + x2.first == x1.first + x2.first) ans[ind] = 2;
        else ans[ind] = 1;
        seg[ind] = {x1.first + x2.first , x1.second + x2.second};
    }
    // long long Query(int ind,int low,int high,int l,int r){
    //     // no overlap
    //     if(l>high || r<low)return 0;

    //     // complete overlap
    //     if(low>=l && high<=r) return seg[ind];

    //     // partial overlap
    //     int mid = (low+high)/2;
    //     long long left = Query(2*ind+1,low,mid,l,r);
    //     long long right = Query(2*ind+2,mid+1,high,l,r);
    //     return max(left,right);
    // }
    // // point update(replace value at index i with val)
    // void Update(int ind,int low,int high,int i,int val){
    //     if(low==high){
    //         seg[ind] = val;
    //         return;
    //     }

    //     int mid = (low+high)/2;
        
    //     if(mid>=i)Update(2*ind+1,low,mid,i,val);
    //     else Update(2*ind+2,mid+1,high,i,val);

    //     seg[ind] = max(seg[2*ind+1],seg[2*ind+2]);
    // }

    // void update(int pos , int value){
    //     Update(0,0,N-1,pos,value);
    // }

    // long long query(int l , int r){
    //     return Query(0,0,N-1,l,r);
    // }
    void build(vector<int>&nums){
        Build(nums,0,0,N-1);
    }
};
