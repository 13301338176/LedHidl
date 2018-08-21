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
	
		��������ʹ����Ӧ������д����������ػ����̡��ػ����̴��루֧��ֱͨ��ʾ����

		#include <hidl/LegacySupport.h>

		int main(int /* argc */, char* /* argv */ []) {
			return defaultPassthroughServiceImplementation<INfc>("nfc");
		}
		defaultPassthroughServiceImplementation �����ṩ�� -impl ��ִ�� dlopen() ��������������Ϊ��ʽ�����ṩ���ػ����̴��루���ڴ���ʽ����ʾ����

		int main(int /* argc */, char* /* argv */ []) {
			sp nfc = new Nfc();
			const status_t status = nfc->registerAsService();
			if (status != ::android::OK) {
				return 1; // or handle error
			}
			// join pool or do other things
		}

		
		add the code to the manifest.xm ������hwservicemanager ���ҵ�ָ����hidl service
			About HIDL configures
			device/linaro/hikey/manifest.xml
			<hal format="hidl">
				<name>android.hardware.led</name>
				<transport>hwbinder</transport>
				<version>1.0</version>
				<interface>
					<name>ILed</name>
					<instance>default</instance>
				</interface>
			</hal>
		
		
2. ʵ��java����hidl service������
	2.1 ��ӿ⣺
		������������ӵ� Android.mk �У�
		LOCAL_JAVA_LIBRARIES += android.hardware.foo-V1.0-java
		��
		������������ӵ� Android.bp �У�
		shared_libs: [
			/* �� */
			"android.hardware.foo-V1.0-java",
		],
		�ÿ⻹���ھ�̬�棺android.hardware.foo-V1.0-java-static��
	2.2 ������������ӵ����� Java �ļ��У�
		import android.hardware.foo.V1_0.IFoo;
		...
		// retry to wait until the service starts up if it is in the manifest
		IFoo server = IFoo.getService(true /* retry */); // throws NoSuchElementException if not available
		IFoo anotherServer = IFoo.getService("second_impl", true /* retry */);
		server.doSomething(��);
		

3. ʵ��C++ ����hidl service������
	���Ƚ� HAL ����ӵ� makefile �У�
		Make��LOCAL_SHARED_LIBRARIES += android.hardware.nfc@1.0
		Soong��shared_libs: [ ��, android.hardware.nfc@1.0 ]
	����������� HAL ͷ�ļ���
		#include <android/hardware/nfc/1.0/IFoo.h>
		��
		// in code:
		sp<IFoo> client = IFoo::getService();
		client->doThing();


4. ��дLED����


