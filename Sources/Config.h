#ifndef CONFIGER_H_
	#define CONFIGER_H_

#define BINGO_DIVER		(0x12U)
#define BIG_DOG_DIVER	(0x13U)
#define USER_DIVER		BINGO_DIVER

#define VERSIONS_MAJOR	(2u)
#define VERSIONS_MINOR	(3u)
#define VERSIONS	"S12 boot V2.3 2017-09-08"
#define CAN_BL_BOOT	(0x0u)

#define CAN_TX_ID	(USER_DIVER)

#define APP_STAR_ADDR		0x20000
#define APP_MAX_ADDR		0x3F000
#define APP_CHECK_STRING	"CHECK OK"
#define APP_TIMEOUT			200
                            
#if (USER_DIVER == BIG_DOG_DIVER)
	#define CHECK_TYPE        "S12G128 Bigdog"
#elif (USER_DIVER == BINGO_DIVER)
	#define CHECK_TYPE        "S12G128 Bingo"
#endif
/**
 *********************************************************************
  2017-9-8 19:33:42
  1.ƥ��FY169-Dragon-V3.0���ư� �޸�can����������
	2017-5-19 17:32:03
	1.������ģ���豸��ַ 0x13
	2.��������У��,�Ǳ��������
	3.���Ź��Ȳ�����
	4.APP����BOOTʱ��1���ӵĵȴ�ʱ��,��ʱ��Ϊ���и��²�������ص�app;
  2017-5-31 09:48:38
    1.�޸���ַ���ò��������app������ʾ�쳣
  2017-7-5 17:57:04
    1.�޸�BOOT������ַ������check��ַ��
 */
#endif
