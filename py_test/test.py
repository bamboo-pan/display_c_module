import sys
import display_c_module as display
# aa=display.get_display_devices()
bb=display.get_device_display_info()
print(bb)
cc=display.get_current_mode('\\\\.\\DISPLAY4')
input()
dd=display.change_resolution('\\\\.\\DISPLAY4',1680,1050,60,0,0,0)
input()
ee=display.change_resolution(*cc)
# # print(aa)
# # print(bb)
# # print(cc)
# print(dd)
# print("")