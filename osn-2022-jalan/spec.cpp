#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

#define mp make_pair
#define fr first
#define sc second

const int MXN = 1e5;
const int MXA = 1e5;

const int MXN2 = 400;

const int MXN3 = 3e3;

const int MXN5 = 400;

const int MXN6 = 3e3;

class ProblemSpec : public BaseProblemSpec
{
	protected:
		int N, ans;
		vector<int> A, T;
		
		void InputFormat()
		{
			LINE(N);
			LINE(A % SIZE(N));
			LINE(T % SIZE(N));
		}
		void OutputFormat()
		{
			LINE(ans);
		}
		void GradingConfig()
		{
			TimeLimit(2);
			MemoryLimit(512);
		}
		void Constraints()
		{
			CONS(1 <= N && N <= MXN);
			CONS(eachElementBetween(A, 1, MXA));
			CONS(eachElementBetween(T, 1, 2));
		}
		void Subtask1()
		{
			Points(6);
			CONS(N == 4);
			CONS(A == vector<int>({3, 2, 2, 3}));
			CONS(T == vector<int>({1, 2, 2, 1}));
		}
		void Subtask2()
		{
			Points(11);
			CONS(N <= MXN2);
			CONS(eachElementBetween(T, 1, 1));
		}
		void Subtask3()
		{
			Points(9);
			CONS(N <= MXN3);
			CONS(eachElementBetween(T, 1, 1));
		}
		void Subtask4()
		{
			Points(10);
			CONS(eachElementBetween(T, 1, 1));
		}
		void Subtask5()
		{
			Points(21);
			CONS(N <= MXN5);
		}
		void Subtask6()
		{
			Points(9);
			CONS(N <= MXN6);
		}
		void Subtask7()
		{
			Points(17);
			CONS(noOneTwo(T));
		}
		void Subtask8()
		{
			Points(17);
		}
	
	private:
		bool eachElementBetween(vector<int> curV, int db, int ub)
		{
			int i, sz = curV.size();
			
			for(i = 0; i < sz; i++)
			{
				if(!(db <= curV[i] && curV[i] <= ub))
				{
					return 0;
				}
			}
			return 1;
		}
		bool noOneTwo(vector<int> curV)
		{
			int i, sz = curV.size();
			
			for(i = 0; i < sz - 1; i++)
			{
				if(curV[i] == 1 && curV[i + 1] == 2)
				{
					return 0;
				}
			}
			return 1;
		}
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
	protected:
		void SampleTestCase1()
		{
			Subtasks({5, 6, 8});
			Input
			({
				"7",
				"3 1 1 2 1 2 3",
				"1 2 1 2 1 2 1"
			});
			Output
			({
				"53"
			});
		}
		void SampleTestCase2()
		{
			Subtasks({2, 3, 4, 5, 6, 7, 8});
			Input
			({
				"2",
				"98427 77780",
				"1 1"
			});
			Output
			({
				"430194"
			});
		}
		void BeforeTestCase()
		{
			A.clear();
			T.clear();
		}
		void TestGroup1()
		{
			Subtasks({1, 5, 6, 8});
			
			CASE(N = 4, A = {3, 2, 2, 3}, T = {1, 2, 2, 1});
		}
		void TestGroup2()
		{
			Subtasks({2, 3, 4, 5, 6, 7, 8});
			
			//(1-4) random
			CASE(N = rnd.nextInt(1, MXN2), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = rnd.nextInt(1, MXN2), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = MXN2, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = MXN2, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			
			//(5) all 1
			CASE(N = MXN2, A = randomArray(N, 1, 1), T = randomArray(N, 1, 1));
			
			//(6) all max
			CASE(N = MXN2, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1));
			
			//(7-8) small N
			CASE(N = 1, A = randomArray(N, 1, MXA), T = {1});
			CASE(N = 2, A = randomArray(N, 1, MXA), T = {1, 1});
		}
		void TestGroup3()
		{
			Subtasks({3, 4, 6, 7, 8});
			
			//(1-4) random
			CASE(N = rnd.nextInt(MXN2 + 1, MXN3), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = rnd.nextInt(MXN2 + 1, MXN3), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = MXN3, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = MXN3, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			
			//(5) all 1
			CASE(N = MXN3, A = randomArray(N, 1, 1), T = randomArray(N, 1, 1));
			
			//(6) all max
			CASE(N = MXN3, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1));
		}
		void TestGroup4()
		{
			Subtasks({4, 7, 8});
			
			//(1-4) random
			CASE(N = rnd.nextInt(MXN3 + 1, MXN), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = rnd.nextInt(MXN3 + 1, MXN), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1));
			
			//(5) all 1
			CASE(N = MXN, A = randomArray(N, 1, 1), T = randomArray(N, 1, 1));
			
			//(6) all max
			CASE(N = MXN, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1));
		}
		void TestGroup5()
		{
			Subtasks({5, 6, 7, 8});
			
			//(1-2) small N
			CASE(N = 1, A = randomArray(N, 1, MXA), T = {2});
			CASE(N = 2, A = randomArray(N, 1, MXA), T = {2, 1});
		}
		void TestGroup6()
		{
			Subtasks({5, 6, 8});
			
			//(1-6) random
			CASE(N = rnd.nextInt(1, MXN5), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 2));
			CASE(N = MXN5, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 2));
			CASE(N = MXN5, controlledRandomArray(N, MXA / 2, MXA));
			CASE(N = MXN5, controlledRandomArray(N, MXA, MXA / 2));
			CASE(N = MXN5, controlledRandomArray(N, MXA / 10, MXA));
			CASE(N = MXN5, controlledRandomArray(N, MXA, MXA / 10));
			
			//(7-12) random prefix sum
			CASE(N = rnd.nextInt(1, MXN5), randomPrefixSum(N, MXA, 0));
			CASE(N = MXN5, randomPrefixSum(N, MXA, 0));
			CASE(N = MXN5, randomPrefixSum(N, MXA, 10));
			CASE(N = MXN5, randomPrefixSum(N, MXA, -10));
			CASE(N = MXN5, randomPrefixSum(N, MXA, 1000));
			CASE(N = MXN5, randomPrefixSum(N, MXA, -1000));
			
			//(13-17) almost no one two
			CASE(N = MXN5, A = randomArray(N, 1, MXA), T = twoOne(N, rnd.nextInt(1, N - 2)), T[N - 1] = 2);
			CASE(N = MXN5, pairsFromMiddle(N, 1, MXA), T[N - 1] = 2);
			CASE(N = MXN5, unbalancedLeft(N, rnd.nextInt(N / 2 - 20, N / 2 + 20), MXA), T[N - 1] = 2);
			CASE(N = MXN5, unbalancedRight(N, rnd.nextInt(N / 2 - 20, N / 2 + 20), MXA), T[N - 1] = 2);
			CASE(N = MXN5, manySameTwoOne(N, rnd.nextInt(N / 2 - 20, N / 2 + 20), MXA), T[N - 1] = 2);
			
			//(18-19) almost all 1
			CASE(N = MXN5, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1), T[N - 1] = 2);
			CASE(N = MXN5, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1), A[N - 1] = 1, T[N - 1] = 2);
			
			//(20-21) almost all 2
			CASE(N = MXN5, A = randomArray(N, 1, MXA), T = randomArray(N, 2, 2), T[0] = 1);
			CASE(N = MXN5, A = randomArray(N, MXA, MXA), T = randomArray(N, 2, 2), A[0] = 1, T[0] = 1);
			
			//(22-23) many same prefix sum
			CASE(N = MXN5, manySamePrefixSum(N, MXA, 10));
			CASE(N = MXN5, manySameMaxPrefixSum(N, MXA, 10));
			
			//(24-25) alternating T
			CASE(N = MXN5, A = randomArray(N, 1, MXA), T = alternatingArray(N));
			CASE(N = MXN5, smartAlternatingArray(N, MXA));
			
			//(26-27) small N
			CASE(N = 2, A = randomArray(N, 1, MXA), T = {1, 2});
			CASE(N = 3, A = randomArray(N, 1, MXA), T = {2, 1, 2});
		}
		void TestGroup7()
		{
			Subtasks({6, 8});
			
			//(1-6) random
			CASE(N = rnd.nextInt(MXN5 + 1, MXN6), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 2));
			CASE(N = MXN6, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 2));
			CASE(N = MXN6, controlledRandomArray(N, MXA / 2, MXA));
			CASE(N = MXN6, controlledRandomArray(N, MXA, MXA / 2));
			CASE(N = MXN6, controlledRandomArray(N, MXA / 10, MXA));
			CASE(N = MXN6, controlledRandomArray(N, MXA, MXA / 10));
			
			//(7-12) random prefix sum
			CASE(N = rnd.nextInt(MXN5 + 1, MXN6), randomPrefixSum(N, MXA, 0));
			CASE(N = MXN6, randomPrefixSum(N, MXA, 0));
			CASE(N = MXN6, randomPrefixSum(N, MXA, 10));
			CASE(N = MXN6, randomPrefixSum(N, MXA, -10));
			CASE(N = MXN6, randomPrefixSum(N, MXA, 1000));
			CASE(N = MXN6, randomPrefixSum(N, MXA, -1000));
			
			//(13-17) almost no one two
			CASE(N = MXN6, A = randomArray(N, 1, MXA), T = twoOne(N, rnd.nextInt(1, N - 2)), T[N - 1] = 2);
			CASE(N = MXN6, pairsFromMiddle(N, 1, MXA), T[N - 1] = 2);
			CASE(N = MXN6, unbalancedLeft(N, rnd.nextInt(N / 2 - 100, N / 2 + 100), MXA), T[N - 1] = 2);
			CASE(N = MXN6, unbalancedRight(N, rnd.nextInt(N / 2 - 100, N / 2 + 100), MXA), T[N - 1] = 2);
			CASE(N = MXN6, manySameTwoOne(N, rnd.nextInt(N / 2 - 100, N / 2 + 100), MXA), T[N - 1] = 2);
			
			//(18-19) almost all 1
			CASE(N = MXN6, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1), T[N - 1] = 2);
			CASE(N = MXN6, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1), A[N - 1] = 1, T[N - 1] = 2);
			
			//(20-21) almost all 2
			CASE(N = MXN6, A = randomArray(N, 1, MXA), T = randomArray(N, 2, 2), T[0] = 1);
			CASE(N = MXN6, A = randomArray(N, MXA, MXA), T = randomArray(N, 2, 2), A[0] = 1, T[0] = 1);
			
			//(22-23) many same prefix sum
			CASE(N = MXN6, manySamePrefixSum(N, MXA, 50));
			CASE(N = MXN6, manySameMaxPrefixSum(N, MXA, 50));
			
			//(24-25) alternating T
			CASE(N = MXN6, A = randomArray(N, 1, MXA), T = alternatingArray(N));
			CASE(N = MXN6, smartAlternatingArray(N, MXA));
		}
		void TestGroup8()
		{
			Subtasks({7, 8});
			
			//(1-2) random
			CASE(N = rnd.nextInt(MXN6 + 1, MXN), A = randomArray(N, 1, MXA), T = twoOne(N, rnd.nextInt(1, N - 1)));
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = twoOne(N, rnd.nextInt(1, N - 1)));
			
			//(3) pairs from middle
			CASE(N = MXN, pairsFromMiddle(N, 1, MXA));
			
			//(4) unbalanced left side
			CASE(N = MXN, unbalancedLeft(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA));
			
			//(5) unbalanced right side
			CASE(N = MXN, unbalancedRight(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA));
			
			//(6-7) many same prefix sum
			CASE(N = rnd.nextInt(MXN6 + 1, MXN), manySameTwoOne(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA));
			CASE(N = MXN, manySameTwoOne(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA));
			
			//(8-9) almost all 1
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1), T[0] = 2);
			CASE(N = MXN, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1), A[0] = 1, T[0] = 2);
			
			//(10-11) all 2
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 2, 2));
			CASE(N = MXN, A = randomArray(N, MXA, MXA), T = randomArray(N, 2, 2));
		}
		void TestGroup9()
		{
			Subtasks({8});
			
			//(1-8) random
			CASE(N = rnd.nextInt(MXN6 + 1, MXN), A = randomArray(N, 1, MXA), T = randomArray(N, 1, 2));
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 2));
			CASE(N = MXN, controlledRandomArray(N, MXA / 2, MXA));
			CASE(N = MXN, controlledRandomArray(N, MXA, MXA / 2));
			CASE(N = MXN, controlledRandomArray(N, MXA / 10, MXA));
			CASE(N = MXN, controlledRandomArray(N, MXA, MXA / 10));
			CASE(N = MXN, controlledRandomArray(N, 100, MXA));
			CASE(N = MXN, controlledRandomArray(N, MXA, 100));
			
			//(9-14) random prefix sum
			CASE(N = rnd.nextInt(MXN6 + 1, MXN), randomPrefixSum(N, MXA, 0));
			CASE(N = MXN, randomPrefixSum(N, MXA, 0));
			CASE(N = MXN, randomPrefixSum(N, MXA, 10));
			CASE(N = MXN, randomPrefixSum(N, MXA, -10));
			CASE(N = MXN, randomPrefixSum(N, MXA, 1000));
			CASE(N = MXN, randomPrefixSum(N, MXA, -1000));
			
			//(15-19) almost no one two
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = twoOne(N, rnd.nextInt(1, N - 2)), T[N - 1] = 2);
			CASE(N = MXN, pairsFromMiddle(N, 1, MXA), T[N - 1] = 2);
			CASE(N = MXN, unbalancedLeft(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA), T[N - 1] = 2);
			CASE(N = MXN, unbalancedRight(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA), T[N - 1] = 2);
			CASE(N = MXN, manySameTwoOne(N, rnd.nextInt(N / 2 - 1000, N / 2 + 1000), MXA), T[N - 1] = 2);
			
			//(20-21) almost all 1
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 1, 1), T[N - 1] = 2);
			CASE(N = MXN, A = randomArray(N, MXA, MXA), T = randomArray(N, 1, 1), A[N - 1] = 1, T[N - 1] = 2);
			
			//(22-23) almost all 2
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = randomArray(N, 2, 2), T[0] = 1);
			CASE(N = MXN, A = randomArray(N, MXA, MXA), T = randomArray(N, 2, 2), A[0] = 1, T[0] = 1);
			
			//(24-25) many same prefix sum
			CASE(N = MXN, manySamePrefixSum(N, MXA, 100));
			CASE(N = MXN, manySameMaxPrefixSum(N, MXA, 100));
			
			//(26-27) alternating T
			CASE(N = MXN, A = randomArray(N, 1, MXA), T = alternatingArray(N));
			CASE(N = MXN, smartAlternatingArray(N, MXA));
		}
	
	private:
		vector<int> randomArray(int sz, int db, int ub)
		{
			int i;
			vector<int> curV;
			
			for(i = 0; i < sz; i++)
			{
				curV.push_back(rnd.nextInt(db, ub));
			}
			return curV;
		}
		void controlledRandomArray(int sz, int ub, int ub2)
		{
			int i;
			
			for(i = 0; i < sz; i++)
			{
				if(rnd.nextInt(1, ub + ub2) <= ub)
				{
					A.push_back(rnd.nextInt(1, ub));
					T.push_back(1);
				}
				else
				{
					A.push_back(rnd.nextInt(1, ub2));
					T.push_back(2);
				}
			}
		}
		void randomPrefixSum(int sz, int ub, int slope)
		{
			long long i, k, last = 0;
			
			for(i = 0; i < sz; i++)
			{
				k = rnd.nextInt(slope * i - (ub - abs(slope)) / 2, slope * i + (ub - abs(slope)) / 2);
				if(k == last)
				{
					if(k - 1 < slope * i - (ub - abs(slope)) / 2)
					{
						k++;
					}
					else if(k + 1 > slope * i + (ub - abs(slope)) / 2)
					{
						k--;
					}
					else
					{
						if(rnd.nextInt(0, 1))
						{
							k++;
						}
						else
						{
							k--;
						}
					}
				}
				if(k > last)
				{
					A.push_back(k - last);
					T.push_back(1);
				}
				else
				{
					A.push_back(last - k);
					T.push_back(2);
				}
				last = k;
			}
		}
		vector<int> twoOne(int sz, int cnt)
		{
			int i;
			vector<int> curV;
			
			for(i = 0; i < sz; i++)
			{
				if(i < cnt)
				{
					curV.push_back(2);
				}
				else
				{
					curV.push_back(1);
				}
			}
			return curV;
		}
		void pairsFromMiddle(int sz, int db, int ub)
		{
			int i;
			
			for(i = 0; i < sz / 2; i++)
			{
				A.push_back(rnd.nextInt(db, ub));
				T.push_back(2);
			}
			for(i = 0; i < sz / 2; i++)
			{
				A.push_back(A[sz / 2 - 1 - i]);
				T.push_back(1);
			}
		}
		void unbalancedLeft(int sz, int cnt, int ub)
		{
			int i, last = 0;
			vector<int> as;
			
			for(i = 0; i < cnt; i++)
			{
				as.push_back(rnd.nextInt(1, ub - (cnt - 1)));
			}
			sort(as.begin(), as.end());
			for(i = 0; i < cnt; i++)
			{
				as[i] += i;
				A.push_back(as[i] - last);
				T.push_back(2);
				last = as[i];
			}
			A.push_back(ub);
			T.push_back(1);
			for(i = 0; i < sz - cnt - 1; i++)
			{
				A.push_back(rnd.nextInt(1, ub));
				T.push_back(1);
			}
		}
		void unbalancedRight(int sz, int cnt, int ub)
		{
			int i, last = 0;
			vector<int> as;
			
			for(i = 0; i < cnt - 1; i++)
			{
				A.push_back(rnd.nextInt(1, ub));
				T.push_back(2);
			}
			A.push_back(ub);
			T.push_back(2);
			for(i = 0; i < sz - cnt; i++)
			{
				as.push_back(rnd.nextInt(1, ub - (sz - cnt - 1)));
			}
			sort(as.begin(), as.end());
			for(i = 0; i < sz - cnt; i++)
			{
				as[i] += i;
				A.push_back(as[i] - last);
				T.push_back(1);
				last = as[i];
			}
		}
		void manySameTwoOne(int sz, int cnt, int ub)
		{
			int i, last;
			vector<int> as;
			
			for(i = 0; i < cnt; i++)
			{
				as.push_back(rnd.nextInt(1, ub - (cnt - 1)));
			}
			sort(as.begin(), as.end());
			last = 0;
			for(i = 0; i < cnt; i++)
			{
				as[i] += i;
				A.push_back(as[i] - last);
				T.push_back(2);
				last = as[i];
			}
			as.clear();
			for(i = 0; i < sz - cnt; i++)
			{
				as.push_back(rnd.nextInt(1, ub - (sz - cnt - 1)));
			}
			sort(as.begin(), as.end());
			last = 0;
			for(i = 0; i < sz - cnt; i++)
			{
				as[i] += i;
				A.push_back(as[i] - last);
				T.push_back(1);
				last = as[i];
			}
		}
		void manySamePrefixSum(int sz, int ub, int cnt)
		{
			int i, k, last = rnd.nextInt(0, cnt - 1), sm = 0;
			vector<int> as;
			
			for(i = 0; i < cnt; i++)
			{
				as.push_back(rnd.nextInt(-ub / 2, ub / 2 - (cnt - 1)));
			}
			sort(as.begin(), as.end());
			for(i = 0; i < cnt; i++)
			{
				as[i] += i;
			}
			for(i = 0; i < sz; i++)
			{
				k = rnd.nextInt(0, cnt - 2);
				if(k >= last)
				{
					k++;
				}
				if(as[k] > sm)
				{
					A.push_back(as[k] - sm);
					T.push_back(1);
				}
				else
				{
					A.push_back(sm - as[k]);
					T.push_back(2);
				}
				last = k;
				sm = as[k];
			}
		}
		void manySameMaxPrefixSum(int sz, int ub, int weight)
		{
			int i, k, last = 0;
			bool bad = 0;
			
			for(i = 0; i < sz; i++)
			{
				if(!bad && rnd.nextInt(1, weight) == 1)
				{
					k = ub / 2;
					bad = 1;
				}
				else
				{
					k = rnd.nextInt(-ub / 2, ub / 2 - 2);
					if(k >= last)
					{
						k++;
					}
					bad = 0;
				}
				if(k > last)
				{
					A.push_back(k - last);
					T.push_back(1);
				}
				else
				{
					A.push_back(last - k);
					T.push_back(2);
				}
				last = k;
			}
		}
		vector<int> alternatingArray(int sz)
		{
			int i;
			vector<int> curV;
			
			for(i = 0; i < sz / 2; i++)
			{
				curV.push_back(2);
				curV.push_back(1);
			}
			return curV;
		}
		void smartAlternatingArray(int sz, int ub)
		{
			int i, k;
			
			for(i = 0; i < sz / 2; i++)
			{
				k = rnd.nextInt(1, ub);
				A.push_back(k);
				T.push_back(2);
				A.push_back(k);
				T.push_back(1);
			}
		}
		
};
