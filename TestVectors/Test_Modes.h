#ifndef LOCKDOWNSSL_MODES_TEST
#define LOCKDOWNSSL_MODES_TEST

#include <iostream>
#include "Modes.h"
#include "Aes.h"

namespace LockdownSSL
{
	namespace Test
	{
		void cbc_aes128_test()
		{
			std::vector<byte> IV = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, };

			std::vector<byte> plaintext
			{
				0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,
				0x7E,0x11,0x73,0x93,0x17,0x2A,0xAE,0x2D,0x8A,0x57,
				0x1E,0x03,0xAC,0x9C,0x9E,0xB7,0x6F,0xAC,0x45,0xAF,
				0x8E,0x51,0x30,0xC8,0x1C,0x46,0xA3,0x5C,0xE4,0x11,
				0xE5,0xFB,0xC1,0x19,0x1A,0x0A,0x52,0xEF,0xF6,0x9F,
				0x24,0x45,0xDF,0x4F,0x9B,0x17,0xAD,0x2B,0x41,0x7B,
				0xE6,0x6C,0x37,0x10,

			};

			std::vector<byte> ciphertext =
			{
				0x76,0x49,0xAB,0xAC,0x81,0x19,0xB2,0x46,0xCE,0xE9,
				0x8E,0x9B,0x12,0xE9,0x19,0x7D,0x50,0x86,0xCB,0x9B,
				0x50,0x72,0x19,0xEE,0x95,0xDB,0x11,0x3A,0x91,0x76,
				0x78,0xB2,0x73,0xBE,0xD6,0xB8,0xE3,0xC1,0x74,0x3B,
				0x71,0x16,0xE6,0x9E,0x22,0x22,0x95,0x16,0x3F,0xF1,
				0xCA,0xA1,0x68,0x1F,0xAC,0x09,0x12,0x0E,0xCA,0x30,
				0x75,0x86,0xE1,0xA7,
			};

			byte key[16] = { 0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C, };

			auto instance = LockdownSSL::Cipher::Aes::getInstance_128(key);

			auto encrypted = LockdownSSL::EncryptionModes::CBC::encrypt(instance, plaintext, IV);

			for (int i = 0; i < ciphertext.size(); i++)
			{
				if (encrypted[i] != ciphertext[i])
				{

					std::cout << "Aes128 CBC encryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CBC encryption passed!" << std::endl;

			auto decrypted = LockdownSSL::EncryptionModes::CBC::decrypt(instance, ciphertext, IV);

			for (int i = 0; i < plaintext.size(); i++)
			{
				if (decrypted[i] != plaintext[i])
				{
					std::cout << "Aes128 CBC decryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CBC decryption passed!" << std::endl;
		}

		void cbcmac_aes128_test()
		{
			std::vector<byte> plaintext
			{
				0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,
				0x7E,0x11,0x73,0x93,0x17,0x2A,0xAE,0x2D,0x8A,0x57,
				0x1E,0x03,0xAC,0x9C,0x9E,0xB7,0x6F,0xAC,0x45,0xAF,
				0x8E,0x51,0x30,0xC8,0x1C,0x46,0xA3,0x5C,0xE4,0x11,
				0xE5,0xFB,0xC1,0x19,0x1A,0x0A,0x52,0xEF,0xF6,0x9F,
				0x24,0x45,0xDF,0x4F,0x9B,0x17,0xAD,0x2B,0x41,0x7B,
				0xE6,0x6C,0x37,0x10,
			};

			std::vector<byte> ciphertext = { 0xa7,0x35,0x6e,0x12,0x7,0xbb,0x40,0x66,0x39,0xe5,0xe5,0xce,0xb9,0xa9,0xed,0x93, };

			byte key[16] = { 0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C, };

			auto instance = LockdownSSL::Cipher::Aes::getInstance_128(key);

			auto encrypted = LockdownSSL::EncryptionModes::CBC_MAC::getMac(instance, plaintext);

			for (int i = 0; i < ciphertext.size(); i++)
			{
				if (encrypted[i] != ciphertext[i])
				{
					std::cout << "Aes128 CBC MAC encryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CBC MAC encryption passed!" << std::endl;
		}

		void cmac_aes128_test()
		{
			byte key[16] = { 0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C, };

			auto instance = LockdownSSL::Cipher::Aes::getInstance_128(key);

			auto data_1 = std::vector<byte>(0);

			std::vector<byte> tag_1 = { 0xBB,0x1D,0x69,0x29,0xE9,0x59,0x37,0x28,0x7F,0xA3,0x7D,0x12,0x9B,0x75,0x67,0x46, };

			std::vector<byte> data_2 = { 0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,0x7E,0x11,0x73,0x93,0x17,0x2A,0xAE,0x2D,0x8A,0x57, };

			std::vector<byte> tag_2 = { 0x7D,0x85,0x44,0x9E,0xA6,0xEA,0x19,0xC8,0x23,0xA7,0xBF,0x78,0x83,0x7D,0xFA,0xDE, };

			auto out_1 = LockdownSSL::EncryptionModes::CMAC::getMac(instance, data_1);

			for (int i = 0; i < tag_1.size(); i++)
			{
				if (out_1[i] != tag_1[i])
				{

					std::cout << " Test 1 : Aes128 CMAC failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Test 1 : Aes128 CMAC passed!" << std::endl;

			auto out_2 = LockdownSSL::EncryptionModes::CMAC::getMac(instance, data_2);

			for (int i = 0; i < tag_2.size(); i++)
			{
				if (out_2[i] != tag_2[i])
				{

					std::cout << "Test 2 : Aes128 CMAC failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Test 2 : Aes128 CMAC passed!" << std::endl;
		}

		void cfb_aes128_test()
		{
			std::vector<byte> IV = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, };

			std::vector<byte> plaintext
			{
				0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,
				0x7E,0x11,0x73,0x93,0x17,0x2A,0xAE,0x2D,0x8A,0x57,
				0x1E,0x03,0xAC,0x9C,0x9E,0xB7,0x6F,0xAC,0x45,0xAF,
				0x8E,0x51,0x30,0xC8,0x1C,0x46,0xA3,0x5C,0xE4,0x11,
				0xE5,0xFB,0xC1,0x19,0x1A,0x0A,0x52,0xEF,0xF6,0x9F,
				0x24,0x45,0xDF,0x4F,0x9B,0x17,0xAD,0x2B,0x41,0x7B,
				0xE6,0x6C,0x37,0x10,

			};

			std::vector<byte> ciphertext =
			{
				0x3B,0x3F,0xD9,0x2E,0xB7,0x2D,0xAD,0x20,0x33,0x34,
				0x49,0xF8,0xE8,0x3C,0xFB,0x4A,0xC8,0xA6,0x45,0x37,
				0xA0,0xB3,0xA9,0x3F,0xCD,0xE3,0xCD,0xAD,0x9F,0x1C,
				0xE5,0x8B,0x26,0x75,0x1F,0x67,0xA3,0xCB,0xB1,0x40,
				0xB1,0x80,0x8C,0xF1,0x87,0xA4,0xF4,0xDF,0xC0,0x4B,
				0x05,0x35,0x7C,0x5D,0x1C,0x0E,0xEA,0xC4,0xC6,0x6F,
				0x9F,0xF7,0xF2,0xE6,
			};

			byte key[16] = { 0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C, };

			auto instance = LockdownSSL::Cipher::Aes::getInstance_128(key);

			auto encrypted = LockdownSSL::EncryptionModes::CFB::encrypt(instance, plaintext, IV);

			for (int i = 0; i < ciphertext.size(); i++)
			{
				if (encrypted[i] != ciphertext[i])
				{

					std::cout << "Aes128 CFB encryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CFB encryption passed!" << std::endl;

			auto decrypted = LockdownSSL::EncryptionModes::CFB::decrypt(instance, ciphertext, IV);

			for (int i = 0; i < plaintext.size(); i++)
			{
				if (decrypted[i] != plaintext[i])
				{

					std::cout << "Aes128 CFB decryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CFB decryption passed!" << std::endl;
		}

		void ofb_aes128_test()
		{
			std::vector<byte> IV = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, };

			std::vector<byte> plaintext
			{
				0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,
				0x7E,0x11,0x73,0x93,0x17,0x2A,0xAE,0x2D,0x8A,0x57,
				0x1E,0x03,0xAC,0x9C,0x9E,0xB7,0x6F,0xAC,0x45,0xAF,
				0x8E,0x51,0x30,0xC8,0x1C,0x46,0xA3,0x5C,0xE4,0x11,
				0xE5,0xFB,0xC1,0x19,0x1A,0x0A,0x52,0xEF,0xF6,0x9F,
				0x24,0x45,0xDF,0x4F,0x9B,0x17,0xAD,0x2B,0x41,0x7B,
				0xE6,0x6C,0x37,0x10,

			};

			std::vector<byte> ciphertext
			{
				0x3B,0x3F,0xD9,0x2E,0xB7,0x2D,0xAD,0x20,0x33,0x34,
				0x49,0xF8,0xE8,0x3C,0xFB,0x4A,0x77,0x89,0x50,0x8D,
				0x16,0x91,0x8F,0x03,0xF5,0x3C,0x52,0xDA,0xC5,0x4E,
				0xD8,0x25,0x97,0x40,0x05,0x1E,0x9C,0x5F,0xEC,0xF6,
				0x43,0x44,0xF7,0xA8,0x22,0x60,0xED,0xCC,0x30,0x4C,
				0x65,0x28,0xF6,0x59,0xC7,0x78,0x66,0xA5,0x10,0xD9,
				0xC1,0xD6,0xAE,0x5E,
			};

			byte key[16] = { 0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C, };

			auto instance = LockdownSSL::Cipher::Aes::getInstance_128(key);

			auto encrypted = LockdownSSL::EncryptionModes::OFB::stream(instance, plaintext, IV);

			for (int i = 0; i < ciphertext.size(); i++)
			{
				if (encrypted[i] != ciphertext[i])
				{

					std::cout << "Aes128 OFB encryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 OFB encryption passed!" << std::endl;

			auto decrypted = LockdownSSL::EncryptionModes::OFB::stream(instance, ciphertext, IV);

			for (int i = 0; i < plaintext.size(); i++)
			{
				if (decrypted[i] != plaintext[i])
				{

					std::cout << "Aes128 OFB decryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 OFB decryption passed!" << std::endl;
		}
	
		void ctr_aes128_test()
		{
			std::vector<byte> Nonce = { 240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255 };

			std::vector<byte> plaintext
			{
				0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,
				0x7E,0x11,0x73,0x93,0x17,0x2A,0xAE,0x2D,0x8A,0x57,
				0x1E,0x03,0xAC,0x9C,0x9E,0xB7,0x6F,0xAC,0x45,0xAF,
				0x8E,0x51,0x30,0xC8,0x1C,0x46,0xA3,0x5C,0xE4,0x11,
				0xE5,0xFB,0xC1,0x19,0x1A,0x0A,0x52,0xEF,0xF6,0x9F,
				0x24,0x45,0xDF,0x4F,0x9B,0x17,0xAD,0x2B,0x41,0x7B,
				0xE6,0x6C,0x37,0x10,

			};

			std::vector<byte> ciphertext =
			{
				0x87,0x4D,0x61,0x91,0xB6,0x20,0xE3,0x26,0x1B,0xEF,
				0x68,0x64,0x99,0x0D,0xB6,0xCE,0x98,0x06,0xF6,0x6B,
				0x79,0x70,0xFD,0xFF,0x86,0x17,0x18,0x7B,0xB9,0xFF,
				0xFD,0xFF,0x5A,0xE4,0xDF,0x3E,0xDB,0xD5,0xD3,0x5E,
				0x5B,0x4F,0x09,0x02,0x0D,0xB0,0x3E,0xAB,0x1E,0x03,
				0x1D,0xDA,0x2F,0xBE,0x03,0xD1,0x79,0x21,0x70,0xA0,
				0xF3,0x00,0x9C,0xEE,
			};

			byte key[16] = { 0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C, };

			auto instance = LockdownSSL::Cipher::Aes::getInstance_128(key);

			auto encrypted = LockdownSSL::EncryptionModes::CTR::stream(instance, plaintext, Nonce, 16);

			for (int i = 0; i < ciphertext.size(); i++)
			{
				if (encrypted[i] != ciphertext[i])
				{

					std::cout << "Aes128 CTR encryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CTR encryption passed!" << std::endl;

			auto decrypted = LockdownSSL::EncryptionModes::CTR::stream(instance, ciphertext, Nonce, 16);

			for (int i = 0; i < plaintext.size(); i++)
			{
				if (decrypted[i] != plaintext[i])
				{

					std::cout << "Aes128 CTR decryption failed at index " << i << std::endl;
					std::cin.get();
					return;
				}
			}
			std::cout << "Aes128 CTR decryption passed!" << std::endl;
		}
	}
}

#endif