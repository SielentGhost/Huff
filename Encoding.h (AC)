#pragma once
#include<stdio.h>
#include"Data.h"


void start_outputing_bits(void) {
	buffer = 0;
	bits_to_go = 8;
}
void start_encoding(void) {
	low = 0l;
	high = TOP_VALUE;
	bits_to_follow = 0l;
}
void output_bit(int bit) {
	buffer >>= 1;
	if (bit)
		buffer |= 0x80;
	bits_to_go--;
	if (bits_to_go == 0) {
		putc(buffer, out);
		bits_to_go = 8;
	}
}
void output_bit_plus_follow(int bit) {
	output_bit(bit);
	while (bits_to_follow > 0) {
		output_bit(!bit);
		bits_to_follow--;
	}
}
void encode_symbol(int symbol) {
	long range;
	range = (long)(high - low) + 1;
	high = low + (range * cum_freq[symbol - 1]) / cum_freq[0] - 1;
	low = low + (range * cum_freq[symbol]) / cum_freq[0];
	while (true) {
		if (high < HALF)
			output_bit_plus_follow(0);
		else if (low >= HALF) {
			output_bit_plus_follow(1);
			low -= HALF;
			high -= HALF;
		}
		else if (low >= FIRST_QTR && high < THIRD_QTR) {
			bits_to_follow++;
			low -= FIRST_QTR;
			high -= FIRST_QTR;
		}
		else
			break;
		low += low;
		high += high + 1;
	}
}

void done_encoding(void) {
	bits_to_follow++;
	if (low < FIRST_QTR)
		output_bit_plus_follow(0);
	else
		output_bit_plus_follow(1);
}
void done_outputing_bits(void) {
	putc(buffer >> bits_to_go, out);
}
void encode(char *infile, char *outfile) {
	int ch, symbol;
	in = fopen(infile, "r+b");
	out = fopen(outfile, "w+b");
	if (in == NULL || out == NULL)
		return;
	start_model();
	start_outputing_bits();
	start_encoding();
	while (true) {
		ch = getc(in);
		if (ch == EOF)
			break;
		symbol = char_to_index[ch];
		encode_symbol(symbol);
		update_model(symbol);
	}
	encode_symbol(EOF_SYMBOL);
	done_encoding();
	done_outputing_bits();
	fclose(in);
	fclose(out);
}
