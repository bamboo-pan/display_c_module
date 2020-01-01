#include "Python.h"
#include "display_c.h"

static PyObject* display_get_display_devices(PyObject* self, PyObject* args)
{
	//input args
	int device_num = 0;
	DISPLAY_DEVICE* display_devices;
	get_display_devices(&display_devices, &device_num);
	PyObject* list = PyList_New(device_num);
	for (int i = 0; i < device_num; i++)
	{
		PyObject* list_temp = PyList_New(2);
		WCHAR* DeviceName = display_devices[i].DeviceName;
		PyObject* temp_device_name = PyUnicode_FromWideChar(DeviceName, -1);
		PyList_SetItem(list_temp, 0, temp_device_name);
		WCHAR* DeviceString = display_devices[i].DeviceString;
		PyObject* temp_device_string = PyUnicode_FromWideChar(DeviceString, -1);
		PyList_SetItem(list_temp, 1, temp_device_string);
		PyList_SetItem(list, i, list_temp);
	}
	return list;

}

static PyObject* display_get_device_display_info(PyObject* self, PyObject* args) {

	int device_num = 0;
	DISPLAY_DEVICE* display_devices;
	get_display_devices(&display_devices, &device_num);
	struct display_device_info* display_device_info_list;
	get_device_display_info(display_devices, device_num, &display_device_info_list);

	PyObject* list = PyList_New(device_num);
	for (int i = 0; i < device_num; i++)
	{
		PyObject* list_temp = PyList_New(3);
		WCHAR* DeviceName = display_devices[i].DeviceName;
		PyObject* temp_device_name = PyUnicode_FromWideChar(DeviceName, -1);
		PyList_SetItem(list_temp, 0, temp_device_name);
		WCHAR* DeviceString = display_devices[i].DeviceString;
		PyObject* temp_device_string = PyUnicode_FromWideChar(DeviceString, -1);
		PyList_SetItem(list_temp, 1, temp_device_string);
		WCHAR* monitor_name = display_device_info_list[i].monitor_name;
		PyObject* temp_monitor_name = PyUnicode_FromWideChar(monitor_name, -1);
		PyList_SetItem(list_temp, 2, temp_monitor_name);
		PyList_SetItem(list, i, list_temp);
	}
	return list;

}

static PyObject* display_get_current_mode(PyObject* self, PyObject* args) {
	WCHAR* device_name;

	if (!PyArg_ParseTuple(args, "u", &device_name))
		return Py_BuildValue("i", 134);
	DEVMODE default_mode;
	default_mode.dmSize = sizeof(DEVMODE);
	default_mode.dmDriverExtra = 0;
	default_mode = get_display_devices_current_mode_devicename(device_name);
	return Py_BuildValue("[ukkklli]", device_name, default_mode.dmPelsWidth, default_mode.dmPelsHeight,
		default_mode.dmDisplayFrequency, default_mode.dmPosition.x, default_mode.dmPosition.y, default_mode.dmDisplayOrientation);
}

static PyObject* display_change_resolution(PyObject* self, PyObject* args) {
	WCHAR* device_name;
	DWORD width;
	DWORD height;
	DWORD frequency;
	LONG x;
	LONG y;
	DWORD Orientation;
	if (!PyArg_ParseTuple(args, "ukkkllk", &device_name, &width, &height, &frequency, &x, &y, &Orientation))
		return Py_BuildValue("i", 444);
	DEVMODE default_mode;
	default_mode.dmSize = sizeof(DEVMODE);
	default_mode.dmDriverExtra = 0;
	default_mode = get_display_devices_current_mode_devicename(device_name);
	int result;
	result = change_resolution_device_name(device_name, width, height, frequency, x, y, Orientation);
	return Py_BuildValue("i", result);

}

// 添加PyMethodDef ModuleMethods[]数组
static PyMethodDef displayMethods[] = {
	// add：可用于Python调用的函数名，Exten_add：C++中对应的函数名
	{"get_display_devices",display_get_display_devices,METH_VARARGS},
	{"get_device_display_info",display_get_device_display_info,METH_VARARGS},
	{"get_current_mode",display_get_current_mode,METH_VARARGS},
	{"change_resolution",display_change_resolution,METH_VARARGS},
	{NULL,NULL,NULL,NULL},
};

// 初始化函数
static struct PyModuleDef displayModule = {
	PyModuleDef_HEAD_INIT,
	"display_c_module",//模块名称
	NULL,
	-1,
	displayMethods
};

void PyInit_display_c_module() {
	PyModule_Create(&displayModule);
}
