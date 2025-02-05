
#include "ECS.hpp"


class World {
    private:
    ECS ECS;

    Scheduler scheduler;
    public:
    void init() {
        ECS.initialize();

    }

};



class Scheduler {
    // 
    void update(float dt) {
        for(auto a)
    }
};
