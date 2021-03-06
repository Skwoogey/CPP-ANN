// ANN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define sqr(x) (x)*(x)

using namespace std;


int main()
{
	srand(time(NULL));

	cout.precision(4);

	int li[4] = {784, 16, 16, 10};

	string out_file = "number_recogniser.ann";

	//ANN sample(out_file);
	ANN sample(3, li);

	ifstream labels, images;

	double iv[784];
	double dov[10];

	labels.open("labels_test.txt", ios::binary);
	images.open("images_test.txt", ios::binary);

	labels.ignore(8, EOF);
	images.ignore(16, EOF);

	double error_sum = 0;

	for (int cycle = 0; cycle < 10000; cycle++)
	{
		unsigned char temp;
		for (int i = 0; i < 784; i++)
		{
			images.read((char*)&temp, 1);
			iv[i] = (double)temp / 255;
		}

		labels.read((char*)&temp, 1);
		for (int i = 0; i < 10; i++)
		{
			dov[i] = (i == temp);
			//cout << ov[i] << endl;
		}

		double *ov = sample.predict(iv);

		for (int i = 0; i < 10; i++)
		{
			error_sum += sqr(dov[i] - ov[i]);
		}

		/*
		cout << "desired output: ";
		for (int i = 0; i < 10; i++)
		cout << dov[i] << " ";
		cout << endl;
		cout << "predicted output: ";
		for (int i = 0; i < 10; i++)
		cout << ov[i] << " ";
		cout << endl;

		system("pause");
		*/
	}
	cout << "before training\n";
	cout << "summed error: " << error_sum << endl;
	cout << "error per prediction: " << error_sum / 10000 << "\n\n";

	labels.close();
	images.close();

	/*training*/
	
	labels.open("labels.txt", ios::binary);
	images.open("images.txt", ios::binary);

	labels.ignore(8, EOF);
	images.ignore(16, EOF);

	cout << "training...\n";

	for (int cycle = 0; cycle < 60000; cycle++)
	{
		unsigned char temp;
		for (int i = 0; i < 784; i++)
		{
			images.read((char*)&temp, 1);
			iv[i] = (double)temp / 255;
		}

		labels.read((char*)&temp, 1);
		for (int i = 0; i < 10; i++)
		{
			dov[i] = (i == temp);
			//cout << ov[i] << endl;
		}

		sample.train(iv, dov);
	}

	cout << "training done\n\n";
		
	labels.close();
	images.close();


	/*testing*/
	
	labels.open("labels_test.txt", ios::binary);
	images.open("images_test.txt", ios::binary);

	labels.ignore(8, EOF);
	images.ignore(16, EOF);

	error_sum = 0;

	for (int cycle = 0; cycle < 10000; cycle++)
	{
		unsigned char temp;
		for (int i = 0; i < 784; i++)
		{
			images.read((char*)&temp, 1);
			iv[i] = (double)temp / 255;
		}

		labels.read((char*)&temp, 1);
		for (int i = 0; i < 10; i++)
		{
			dov[i] = (i == temp);
			//cout << ov[i] << endl;
		}

		double *ov = sample.predict(iv);

		for (int i = 0; i < 10; i++)
		{
			error_sum += sqr(dov[i] - ov[i]);
		}

		
		cout << "desired output: ";
		for (int i = 0; i < 10; i++)
			cout << dov[i] << " ";
		cout << endl;
		cout << "predicted output: ";
		for (int i = 0; i < 10; i++)
			cout << ov[i] << " ";
		cout << endl;

		system("pause");
		
	}

	cout << "after training\n";
	cout << "summed error: "<< error_sum << endl;
	cout << "error per prediction: "<<error_sum / 10000 << endl;

	labels.close();
	images.close();
	
	sample.save(out_file);

	system("pause");

    return 0;
}

