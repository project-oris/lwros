#include "lwcommhello.h"
#include "comm/include/api/user_api.h"
#include "rosapi/include/rclapi/rclapi.h"

int mycallback(SubscriptionHandle ctx, const void *msg, size_t msgsize)
{

}

int main()
{
    //std::cout <<"Helo"<<std::endl;
    //my_tests();
    //printf("Helo\n");

    NodeHandle mynode = create_node("myNode");

    SubscriptionHandle mysub = create_subscription(mynode, "mytopic", "std::string", mycallback);

    wait_for_stop(mynode);
    
}