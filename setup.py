from setuptools import setup,Extension
package='display_pkg_c'
module1=Extension('display_c_module',
                  sources=['display_c_module.c','display_c.c',],
				  define_macros = [('UNICODE', 1)],
                  include_dirs = [],
                  library_dirs = [],
                  libraries = ['User32']
                  )

setup(name='display_c_module',
      version='1.0',
      description = 'display setting tool',
      author='bamboo.pan',
      author_email='1422073495@qq.com',
      keywords='display',
      ext_modules=[module1])