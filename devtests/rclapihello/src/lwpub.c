#include "lwcommhello.h"
#include "comm/include/api/user_api.h"
#include "rosapi/include/rclapi/rclapi.h"

int main()
{
    //std::cout <<"Helo"<<std::endl;
    //my_tests();
    //printf("Helo\n");

    NodeHandle mynode = create_node("myNode");

    PublisherHandle mypub = create_publisher(mynode, "mytopic", "std::string");

    char *mydata = "mydatastring";
    publish_topic(mypub, mydata, strlen(mydata));

    wait_for_stop(mynode);
}