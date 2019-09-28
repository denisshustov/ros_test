#!/usr/bin/env python

from beginner_tutorials.srv import AddTwoInts, AddTwoIntsResponse
import rospy

def handle_two_ints(req):
    print "result  %s + %s = %s"%(req.a, req.b, (req.a + req.b))
    return AddTwoIntsResponse(req.a + req.b)

def add_two_ints_server():
    rospy.init_node('add_two_ints_server')
    s = rospy.Service("add_two_ints", AddTwoInts, handle_two_ints)
    print('Read to add')
    rospy.spin()

if __name__=='__main__':
    add_two_ints_server()
