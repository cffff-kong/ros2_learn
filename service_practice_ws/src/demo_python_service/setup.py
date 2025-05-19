from setuptools import find_packages, setup

package_name = 'demo_python_service'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        ('share/' + package_name+"/resource", ['resource/test.jpg']),

    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='kongdechang',
    maintainer_email='1092555104@qq.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'face_detect_service= demo_python_service.face_detect_node:main',
            'face_detect_client= demo_python_service.face_detect_client_node:main',

        ],
    },
)
