

//
// int value[MAXN];
//
// template <typename T>
// class BaseStrategy {
// public:
//     BaseStrategy(vector<T>& dataPtr): dataPtr(dataPtr) {}
//     virtual void reduce(T& cum, T cur)=0;
//     virtual T getInitValue(int curNode) {return T();}
//     vector<T>& dataPtr;
// };
//
// class SubtreeSizeStrategy : public BaseStrategy<int> {
//     using BaseStrategy::BaseStrategy;
//     void reduce(int& cum, int cur) override {
//         cum += cur;
//     }
//     int getInitValue(int curNode) override {return 1;}
// };
//
// class SubtreeSumStrategy : public BaseStrategy<ll> {
//     using BaseStrategy::BaseStrategy;
//     void reduce(ll& cum, ll cur) override {
//         cum += cur;
//     }
//     ll getInitValue(int curNode) override {return value[curNode];}
// };
//
//
// class Tree {
// public:
//     int n;
//     vvi G;
//
//     Tree(int n): n(n) {
//         G = vvi(n+1, vi());
//         repin(i,1,n-1) {
//             int x,y;
//             cin >> x >> y;
//             G[x].push_back(y);
//             G[y].push_back(x);
//         }
//     }
//
//     template <typename... Strategies>
//     auto registerStrategies(std::tuple<Strategies...>&& strategies) {
//         return [&strategies] {
//
//         };
//     }
//
//
//
// };
//
// Tree tree(2);
//
// int main() {
//
//     vector<int> subtreeSize;
//     vector<ll> subtreeSum;
//     tree.registerStrategies(std::make_tuple(SubtreeSizeStrategy(subtreeSize), SubtreeSumStrategy(subtreeSum)));
// }