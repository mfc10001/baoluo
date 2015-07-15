#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
#include "StaticMemory.h"
/** @class ObjectManager
 * ʵ�������ڴ�ش�������
 * Ҫ��������ȱʡ���캯��
 */
template<typename T>
class ObjectManager
{
public:
	typedef T ObjectType;

	static ObjectType* Create(StaticMemory* pool)
	{
		void* pobject=pool->Malloc(sizeof(T));
		new(pobject) ObjectType();
		return static_cast<ObjectType*>(pobject);
	}
	static void Delete(StaticMemory* pool, ObjectType* pobject)
	{
		pobject->~ObjectType();
		pool->Free(pobject);
	}
};
#endif

