hidl demo
1. �Կ���LEDΪ������demo�ı�д
1.1 ��дled.hal ��types.hal
1.2 ִ��update-makefiles.sh �����ļ�
	�½�defalut�ļ���
	
1.3 ʵ��android.hardware.led@1.0-impl��android.hardware.led@1.0-service
	��дandroid.bp
		cc_library_shared {
			name: "android.hardware.led@1.0-impl",
			defaults: ["hidl_defaults"],
			relative_install_path: "hw",
			proprietary: true,
			srcs: ["Consumerled.cpp"],
			shared_libs: [
				"libhidlbase",
				"libhidltransport",
				"libhardware",
				"liblog",
				"libutils",
				"android.hardware.led@1.0",
			],
		}

		cc_binary {
			relative_install_path: "hw",
			defaults: ["hidl_defaults"],
			name: "android.hardware.led@1.0-service",
			proprietary: true,
			init_rc: ["android.hardware.led@1.0-service.rc"],
			srcs: ["service.cpp"],

			shared_libs: [
				"liblog",
				"libhardware",
				"libhidlbase",
				"libhidltransport",
				"libutils",
				"android.hardware.led@1.0",
			],

		}
	


2. ʵ��java����hidl service������
3. ʵ��C++ ����hidl service������
4. ��дLED����


