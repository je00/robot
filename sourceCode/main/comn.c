#include "INCLUDES.h"

/*
 * 与我方小车通讯的程序
 *	@author: Ting
 *	@date:	 13th September, 2014
 */


#define QLENGTH 100

unsigned char dataPack[8];

struct QUEUE{
	unsigned char data[QLENGTH];
	unsigned char head;
	unsigned char end;
} queue;

/*
 * 队列初始化
 */
unsigned char queue_init() 
{
	queue.head = 0;
	queue.end = 0;
}

/*
 *	判断队列是否已空
 *	@return: 已空返回1，否则返回0
 */
unsigned char queue_empty() 
{
	return (queue.head == queue.end);
}

/*
 *	判断队列是否已满
 *	@return: 已满返回1，否则返回0
 */
unsigned char queue_full() 
{
	return (queue.head == (queue.end + 1) % QLENGTH);
}

/*
 * 出队列一个字符，调用前需先判断队列是否已空
 * @return: 返回取出的字符串
 */
unsigned char queue_out_char() 
{
	queue.head = (queue.head + 1) % QLENGTH;
	return queue.data[queue.head];
}

/*
 *  进队列一个字符，调用前需先判断队列是否已满
 */
void queue_append(unsigned char buf) 
{
	queue.end = (queue.end + 1) % QLENGTH;
	queue.data[queue.end] = buf;
}

/*
 *	出队列num个字符
 *	@return: 返回实际取出的字符数
 */
unsigned char queue_out_chars(unsigned char* buf, unsigned char num) 
{
	unsigned char i;
	for(i = 0; i < num; i++) {
		if(queue_empty()) return i;
		else
			*(buf + i) = queue_out_char();
	}
	return num;
}


/*
 * CRC-16 余项表
 * G = x8 + x5 + x4 + 1
 */
unsigned short CRC_table[256]={
	0x0000, 0x8005, 0x800F, 0x000A, 0x801B, 0x001E, 0x0014, 0x8011,
	0x8033, 0x0036, 0x003C, 0x8039, 0x0028, 0x802D, 0x8027, 0x0022,
	0x8063, 0x0066, 0x006C, 0x8069, 0x0078, 0x807D, 0x8077, 0x0072,
	0x0050, 0x8055, 0x805F, 0x005A, 0x804B, 0x004E, 0x0044, 0x8041,
	0x80C3, 0x00C6, 0x00CC, 0x80C9, 0x00D8, 0x80DD, 0x80D7, 0x00D2,
	0x00F0, 0x80F5, 0x80FF, 0x00FA, 0x80EB, 0x00EE, 0x00E4, 0x80E1,
	0x00A0, 0x80A5, 0x80AF, 0x00AA, 0x80BB, 0x00BE, 0x00B4, 0x80B1,
	0x8093, 0x0096, 0x009C, 0x8099, 0x0088, 0x808D, 0x8087, 0x0082,
	0x8183, 0x0186, 0x018C, 0x8189, 0x0198, 0x819D, 0x8197, 0x0192,
	0x01B0, 0x81B5, 0x81BF, 0x01BA, 0x81AB, 0x01AE, 0x01A4, 0x81A1,
	0x01E0, 0x81E5, 0x81EF, 0x01EA, 0x81FB, 0x01FE, 0x01F4, 0x81F1,
	0x81D3, 0x01D6, 0x01DC, 0x81D9, 0x01C8, 0x81CD, 0x81C7, 0x01C2,
	0x0140, 0x8145, 0x814F, 0x014A, 0x815B, 0x015E, 0x0154, 0x8151,
	0x8173, 0x0176, 0x017C, 0x8179, 0x0168, 0x816D, 0x8167, 0x0162,
	0x8123, 0x0126, 0x012C, 0x8129, 0x0138, 0x813D, 0x8137, 0x0132,
	0x0110, 0x8115, 0x811F, 0x011A, 0x810B, 0x010E, 0x0104, 0x8101,
	0x8303, 0x0306, 0x030C, 0x8309, 0x0318, 0x831D, 0x8317, 0x0312,
	0x0330, 0x8335, 0x833F, 0x033A, 0x832B, 0x032E, 0x0324, 0x8321,
	0x0360, 0x8365, 0x836F, 0x036A, 0x837B, 0x037E, 0x0374, 0x8371,
	0x8353, 0x0356, 0x035C, 0x8359, 0x0348, 0x834D, 0x8347, 0x0342,
	0x03C0, 0x83C5, 0x83CF, 0x03CA, 0x83DB, 0x03DE, 0x03D4, 0x83D1,
	0x83F3, 0x03F6, 0x03FC, 0x83F9, 0x03E8, 0x83ED, 0x83E7, 0x03E2,
	0x83A3, 0x03A6, 0x03AC, 0x83A9, 0x03B8, 0x83BD, 0x83B7, 0x03B2,
	0x0390, 0x8395, 0x839F, 0x039A, 0x838B, 0x038E, 0x0384, 0x8381,
	0x0280, 0x8285, 0x828F, 0x028A, 0x829B, 0x029E, 0x0294, 0x8291,
	0x82B3, 0x02B6, 0x02BC, 0x82B9, 0x02A8, 0x82AD, 0x82A7, 0x02A2,
	0x82E3, 0x02E6, 0x02EC, 0x82E9, 0x02F8, 0x82FD, 0x82F7, 0x02F2,
	0x02D0, 0x82D5, 0x82DF, 0x02DA, 0x82CB, 0x02CE, 0x02C4, 0x82C1,
	0x8243, 0x0246, 0x024C, 0x8249, 0x0258, 0x825D, 0x8257, 0x0252,
	0x0270, 0x8275, 0x827F, 0x027A, 0x826B, 0x026E, 0x0264, 0x8261,
	0x0220, 0x8225, 0x822F, 0x022A, 0x823B, 0x023E, 0x0234, 0x8231,
	0x8213, 0x0216, 0x021C, 0x8219, 0x0208, 0x820D, 0x8207, 0x0202
};

/*
 * CRC-16 快速算法
 */
unsigned short do_CRC(unsigned char *data, int length)
{
	unsigned short fcs = 0x0000;
	while(length > 0) {
		fcs = fcs << 8;
		fcs = fcs^CRC_table[fcs>>8^*data];
		length--;
		data++;
	}
	return fcs;

}

/*
 * 进行CRC校验
 * @parameter:	data:要检验的数据	length:数据的长度
 * @return: 	检验成功返回1，否则返回0
 */
unsigned char CRC_checkout(unsigned char *data, int length) 
{
	unsigned short fcs = do_CRC(data, length-2);
	if(*(data + (length-2)) == (unsigned char)(fcs >> 8) 
			&& *(data + (length-1)) == (unsigned char)fcs) {
		return 1;
	}
	return 0;
}

/*
 * 从队列中过滤一组友方的状态
 */
unsigned char getFriendStatus() 
{
	unsigned char i;
	unsigned char buf[8];
	
	while(buf[0] != 0xff) {				// 寻找帧头
		if(queue_out_chars(buf, 1) != 1) 
			return 0;
	}
	if(queue_out_chars(&buf[1], 1) != 1) {
		return 0;
	}
	if(buf[1] == myFriend.id
				&& queue_out_chars(&buf[2], 6) == 6
				&& buf[7] == 0xfe
				&& CRC_checkout(buf, 7)) {	
		for(i = 0; i < 7; i++) {uart1_put_char(buf[i]);} 
		count2 = 0;
		myFriend.track = buf[2];
		myFriend.dir = buf[3];
		myFriend.detectCode = buf[4];
		return 1;	
	}	
	else
		getFriendStatus();
	return 0; 
}

/*
 * 打包我方状态信息组
 * 数据格式：0xff + myId + vehicle.track + vehicle.dir + sensor.detectCode + crc_h + crc_l + 0xfe
 */
 #define myId 0x34
 void packData()
 {
	unsigned short fcs;
	dataPack[0] = 0xff;
	dataPack[1] = myId;
	dataPack[2] = vehicle.track;
	dataPack[3] = vehicle.dir;
	dataPack[4] = sensor.detectCode;
	fcs = do_CRC(dataPack, 5);
	dataPack[5] = (unsigned char)(fcs >> 8);		// 高字节	
	dataPack[6] = (unsigned char)fcs;				// 低字节
	dataPack[7] = 0xfe;
 }

 void packDanger()
 {
	unsigned short fcs;
	dataPack[0] = 0xff;
	dataPack[1] = myId;
	dataPack[2] = 0xee;
	dataPack[3] = 0xee;
	dataPack[4] = 0xee;
	fcs = do_CRC(dataPack, 5);
	dataPack[5] = (unsigned char)(fcs >> 8);		// 高字节	
	dataPack[6] = (unsigned char)fcs;				// 低字节
	dataPack[7] = 0xfe;
 }

/*
 * 发送信息组
 */
 void txData()
 {
 	unsigned char i;
	for(i = 0; i < 8; i++) {
		uart1_put_char(dataPack[i]);
	}
 }

/*
 * 轨道简化，跨轨道情况视为在较靠外轨道
 * @return：0/1/2/3（在轨道0/在轨道1/在轨道2/在角落）
 */
unsigned char trackSimplify(unsigned char track)
{
	switch(track) {
		CASE_TRACK0 return 0;
		CASE_TRACK1 return 1;
		CASE_TRACK2 return 2;
		CASE_CORNER return 3;
	}
}

/*
 * 设置友方位置
 */
void setLocFriend(unsigned char locFriend)
{
	vehicle.locFriend = locFriend;
	vehicle.locEnemy = sensor.detectCode | ~(locFriend);
}

 /*
  * 与友方数据进行匹配分析
  */
void statusMatch()
{
	unsigned char trackSelf = trackSimplify(vehicle.track);
	unsigned char trackFrnd = trackSimplify(myFriend.track);
	unsigned char locFriendPV[2] = {0xff, 0xff};	// 友方位置可能的值
	vehicle.locFriend = 0xff;
	if((trackFrnd == 3) || (myFriend.dir == 0xee)) {
		setLocFriend(0x3e);
	} 
	else if(trackFrnd ==2 && (vehicle.dir == FACE_EDGE)) {
		setLocFriend(0x3e);
	}
END:	;//printData();
}

/*
 * 发送调试数据帧，包含我方与友方的轨道、朝向、检测码，以及敌方、友方相对我方的位置
 * 使用串口猎人过滤
 */
void printData()
{
	uart1_put_char(0xA5);
	uart1_put_char(0xf0);
	uart1_put_char(vehicle.track);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf1);
	uart1_put_char(vehicle.dir);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf2);
	uart1_put_char(sensor.detectCode);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf3);
	uart1_put_char(vehicle.locEnemy);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf4);
	uart1_put_char(myFriend.track);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf5);
	uart1_put_char(myFriend.dir);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf6);
	uart1_put_char(myFriend.detectCode);
	uart1_put_char(0xAA);

	uart1_put_char(0xA5);
	uart1_put_char(0xf7);
	uart1_put_char(vehicle.locFriend);
	uart1_put_char(0xAA); 
}
