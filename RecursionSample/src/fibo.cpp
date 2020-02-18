/*
 * fibo.cpp
 *
 *  Created on: Feb 18, 2020
 *      Author: sin
 */
#include <cstdlib>
#include <iostream>
#include <chrono>

unsigned long long fibo(const unsigned long long & n) {
	if ( n <= 2 )
		return 1;
	return fibo(n-1) + fibo(n-2);
}

int main(const int argc, const char * argv[]) {

    std::chrono::system_clock::time_point  start, end;
    std::time_t time_stamp;

    start = std::chrono::system_clock::now(); // 計測開始時間
    unsigned long long fn = fibo(43);
    end = std::chrono::system_clock::now();  // 計測終了時間

    std::cout << "nth fibo number = "<< (unsigned long) fn << std::endl;
    // 処理に要した時間
    auto time = end - start;

    // 処理を開始した時間（タイムスタンプ）
    time_stamp = std::chrono::system_clock::to_time_t(start);
    //std::cout << std::ctime(&time_stamp);

    // 処理に要した時間をミリ秒に変換
    auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(time).count();
    std::cout << msec << " msec" << std::endl;

	return EXIT_SUCCESS;
}
