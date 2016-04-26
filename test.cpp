#include <jni.h>
#include <android/log.h>

#define JNI_FUNC(name) JNIEXPORT void JNICALL Java_test_game_JaiTextMain_ ## name
#define NAME_PRE "void Java_test_game_JaiTextMain"
#define MY_FUNC (__func__ + sizeof(NAME_PRE))

//#include <string>
#include <string.h>
#define must(SUC) if(!(SUC)) throw int(__LINE__);

void CallJavaThings(JNIEnv * env)
{
	try {
		jclass classObj = env->FindClass("test/game/JaiTextMain");
		must(classObj);
		auto mid = env->GetStaticMethodID(classObj, "JavaRun", "(I)Ljava/lang/String;");
		must(mid);
		
		auto res = (jstring)env->CallStaticObjectMethod(classObj, mid, 123);
		auto cstr = env->GetStringUTFChars(res, nullptr);
		
		__android_log_print(ANDROID_LOG_INFO, "test.game", "the string from java is %s", cstr);
	} catch(int line_no)
	{
		__android_log_print(ANDROID_LOG_INFO, "test.game", "throw from %s %d", __FILE__, line_no);
	}
}

extern "C" {
	JNI_FUNC(ShowSomeThing)(JNIEnv * env, jobject obj, jint num)
	{
		__android_log_print(ANDROID_LOG_INFO, "test.game", "this is printed by cpp %d", num);

		CallJavaThings(env);
	}
	jint JNI_OnLoad(JavaVM* vm, void *reserved)
	{
		__android_log_print(ANDROID_LOG_INFO, "test.game", __FUNCTION__);
		return JNI_VERSION_1_4;
	}
}
