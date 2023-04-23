#!/usr/bin/python3 -f

import os, sys, platform, subprocess

print("OS %s" % os.name)
print("System %s" % platform.system())

new_env = os.environ.copy()

system_name = platform.system()

if system_name.find("MSYS_NT") >= 0 or system_name == "Windows" :
	cmake_tool = 'cmake'
	make_tool = 'nmake -nologo'
	generator = "NMake Makefiles"
elif system_name.find("Linux") >= 0 :
	cmake_tool = 'cmake'
	make_tool = 'make'
	generator = "Unix Makefiles"
	new_env['LD_LIBRARY_PATH'] = os.getcwd() + '/bin'

is_dynamic = 0
for dir in ('static_binding', 'runtime_binding') :
	build_dir = '_build/' + dir

	new_env['RUNTIME_BINDING'] = "%d" % is_dynamic
	os.makedirs(build_dir, mode=0o775, exist_ok=True)
	sp = subprocess.Popen(args=(cmake_tool, '-G', generator, '../..'), cwd=build_dir,
			env=new_env)
	sp.communicate()

	subprocess.check_call(make_tool.split(), cwd=build_dir)

	bin_dir = os.getcwd() + '/bin'
	exe = bin_dir + '/cpp_demo_' + dir
#	print("Exe = %s, CWD = %s" % (exe, os.getcwd()))
	sp = subprocess.Popen(args=(exe), cwd=bin_dir, env=new_env)
	sp.communicate()

	is_dynamic = (1 + is_dynamic) % 2


