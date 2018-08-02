#!/usr/bin/env python2

# Copyright (C) 2018 Christian Berger
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

# This is the Python version of libcluon's OD4Session:
import OD4Session

# This is our example message specification.
import MyExampleMessageSpec_pb2

# Callback for a message of interest.
def onMessage(msg, timeStamps):
   print "sent: " + str(timeStamps[0]) + ", received: " + str(timeStamps[1]) + ", sample time stamps: " + str(timeStamps[2])
   print msg

# "Main" part.
listener = OD4Session.OD4Session(cid=253) # Connect to running OD4Session at CID 253.
listener.registerMessageCallback(400, onMessage, MyExampleMessageSpec_pb2.my_TestMessage)
listener.connect()
listener.run()
