/*
 * This software is provided under the terms of the GNU General
 * Public License as published by the Free Software Foundation.
 *
 * Copyright (c) 2003-2005 Tom Portegys, All Rights Reserved.
 * Permission to use, copy, modify, and distribute this software
 * and its documentation for NON-COMMERCIAL purposes and without
 * fee is hereby granted provided that this copyright notice
 * appears in all copies.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.
 */

/*
 * The Mona maze-making program.
 * Generate mazes starting with the given maze parameter state
 * that are "interesting", as defined by successful, varied,
 * and lengthy goal searches. Mazes are generated by hill-climbing
 * parameter state space. Prints generated maze parameter states
 * and optionally creates input files suitable for testing Mona
 * and SNNS (Stuttgart Neural Network Simulator) neural networks.
 */

#include "mazePathFinder.hpp"

char *Usage[] =
{
    "maze_maker\n",
    "      -steps <number of steps in parameter space>\n",
    "      -mazes <number of random meta-mazes generated per parameter state>\n",
    "      -instances <number of random maze instances generated per meta-maze>\n",
    "      [-randomSeed <random seed>]\n",
    "      -numOutput <number of generated maze parameter states to print>\n",
    "      [-monaFilePrefix <file prefix to store maze in Mona format>]\n",
    "          (file name: <prefix><number>.pat)\n",
    "      [-snnsFilePrefix <file prefix to store maze in SNNS format>]\n",
    "          (file name: <prefix><number>-<instance>.pat)\n",
    "      -numRooms <number of rooms>\n",
    "      [-deltaRooms <maximum variation in number of rooms>]\n",
    "      -numDoors <number of doors>\n",
    "      [-deltaDoors <maximum variation in number of doors>]\n",
    "      -numGoals <number of goals>\n",
    "      [-deltaGoals <maximum variation in number of goals>]\n",
    "      -contextSizes <context level sizes> (comma-separated list)\n",
    "      [-deltaContextSizes <maximum variation in context sizes>]\n",
    "      -effectDelayScale <effect delay scale> (> 0)\n",
    "      [-deltaEffectDelayScale <maximum variation in effect delay scale>]\n",
    "      [-twoway (if room A->B, then B->A)]\n",
    "      [-markPath (uniquely mark interior path rooms)]\n",
    NULL
};

void printUsage()
{
    for (int i = 0; Usage[i] != NULL; i++)
    {
        fprintf(stderr, Usage[i]);
    }
}


// Generated mazes.
list<MazePathFinder *> MazeList;

// Maze evaluation.
void evaluate(MazePathFinder *, int mazes, int instances);

// Dump Mona-format files.
void dumpMonaFiles(char *);

// Dump SNNS-format files.
void dumpSNNSfiles(char *);

// Global random numbers.
Random *randomizer;

int
main(int argc, char *argv[])
{
    int step,i,j,k;
    int steps,mazes,instances,numOutput;
    int numRooms,numDoors,numGoals,effectDelayScale;
    vector<int> contextSizes;
    int deltaRooms,deltaDoors,deltaGoals,deltaEffectDelayScale;
    vector<int> deltaContextSizes;
    MazePathFinder *baseState,*testState,*bestState;
    list<MazePathFinder *> work;
    list<MazePathFinder *>::iterator itr;
    char *monaPrefix;
    char *snnsPrefix;

    // Get options.
    steps = mazes = instances = numOutput = -1;
    numRooms = numDoors = numGoals = effectDelayScale = -1;
    deltaRooms = deltaDoors = deltaGoals = deltaEffectDelayScale = -1;
    baseState = new MazePathFinder();
    assert(baseState != NULL);
    monaPrefix = snnsPrefix = NULL;
    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-steps") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            steps = atoi(argv[i]);
            if (steps < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-mazes") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            mazes = atoi(argv[i]);
            if (mazes < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-instances") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            instances = atoi(argv[i]);
            if (instances < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-numOutput") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            numOutput = atoi(argv[i]);
            if (numOutput < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-monaPrefix") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            monaPrefix = argv[i];
            continue;
        }

        if (strcmp(argv[i], "-snnsPrefix") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            snnsPrefix = argv[i];
            continue;
        }

        if (strcmp(argv[i], "-randomSeed") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            baseState->metaSeed = atoi(argv[i]);
            continue;
        }

        if (strcmp(argv[i], "-numRooms") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            numRooms = baseState->numRooms = atoi(argv[i]);
            continue;
        }

        if (strcmp(argv[i], "-deltaRooms") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            deltaRooms = atoi(argv[i]);
            if (deltaRooms < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-numDoors") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            numDoors = baseState->numDoors = atoi(argv[i]);
            continue;
        }

        if (strcmp(argv[i], "-deltaDoors") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            deltaDoors = atoi(argv[i]);
            if (deltaDoors < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-twoway") == 0)
        {
            baseState->twoway = true;
            continue;
        }

        if (strcmp(argv[i], "-markPath") == 0)
        {
            baseState->markPath = true;
            continue;
        }

        if (strcmp(argv[i], "-numGoals") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            numGoals = baseState->numGoals = atoi(argv[i]);
            continue;
        }

        if (strcmp(argv[i], "-deltaGoals") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            deltaGoals = atoi(argv[i]);
            if (deltaGoals < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-contextSizes") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            char *s,*s2;
            s = argv[i]; s2 = strchr(s, ',');
            while (s != NULL)
            {
                if (s2 != NULL) s2[0] = '\0';
                contextSizes.push_back(atoi(s));
                baseState->contextSizes.push_back(atoi(s));
                if (s2 != NULL)
                {
                    s2[0] = ','; s2++;
                    s = s2; s2 = strchr(s, ',');
                }
                else
                {
                    s = s2;
                }
            }
            continue;
        }

        if (strcmp(argv[i], "-deltaContextSizes") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            char *s,*s2;
            s = argv[i]; s2 = strchr(s, ',');
            while (s != NULL)
            {
                if (s2 != NULL) s2[0] = '\0';
                deltaContextSizes.push_back(atoi(s));
                if (s2 != NULL)
                {
                    s2[0] = ','; s2++;
                    s = s2; s2 = strchr(s, ',');
                }
                else
                {
                    s = s2;
                }
            }
            continue;
        }

        if (strcmp(argv[i], "-effectDelayScale") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            effectDelayScale = baseState->effectDelayScale = atoi(argv[i]);
            continue;
        }

        if (strcmp(argv[i], "-deltaEffectDelayScale") == 0)
        {
            i++;
            if (i >= argc)
            {
                printUsage();
                exit(1);
            }
            deltaEffectDelayScale = atoi(argv[i]);
            if (deltaEffectDelayScale < 0)
            {
                printUsage();
                exit(1);
            }
            continue;
        }

        if (strcmp(argv[i], "-version") == 0)
        {
            Maze::version();
            exit(0);
        }

        printUsage();
        exit(1);
    }

    if (steps < 0 || mazes < 0 || instances < 0 || numOutput < 0)
    {
        printUsage();
        exit(1);
    }

    if (numRooms < 0 || numDoors < 0 ||
        numGoals < 0 || contextSizes.size() == 0 ||
        effectDelayScale <= 0)
    {
        printUsage();
        exit(1);
    }
    if (deltaContextSizes.size() > 0 &&
        baseState->contextSizes.size() != deltaContextSizes.size())
    {
        fprintf(stderr, "Delta Context Sizes mismatches Context Sizes\n");
        printUsage();
        exit(1);
    }

    if (baseState->metaSeed == INVALID_RANDOM)
    {
        baseState->metaSeed = time(NULL);
    }
    randomizer = new Random(baseState->metaSeed);
    assert(randomizer != NULL);

    // Add base state to maze list.
    evaluate(baseState, mazes, instances);
    MazeList.push_back(baseState);

    // Hill-climb.
    for (step = 0; step < steps; step++)
    {
        baseState = *MazeList.begin();

        // Generate new maze from base.
        testState = baseState->clone();
        evaluate(testState, mazes, instances);
        MazeList.push_back(testState);

        // Vary rooms.
        i = (baseState->numRooms - 1) - numRooms;
        if (i < 0) i = -i;
        if (deltaRooms == -1 || i <= deltaRooms)
        {
            if (baseState->numRooms > 1)
            {
                testState = baseState->clone();
                testState->numRooms--;
                evaluate(testState, mazes, instances);
                MazeList.push_back(testState);
            }
        }
        i = (baseState->numRooms + 1) - numRooms;
        if (i < 0) i = -i;
        if (deltaRooms == -1 || i <= deltaRooms)
        {
            testState = baseState->clone();
            testState->numRooms++;
            evaluate(testState, mazes, instances);
            MazeList.push_back(testState);
        }

        // Vary doors.
        i = (baseState->numDoors - 1) - numDoors;
        if (i < 0) i = -i;
        if (deltaDoors == -1 || i <= deltaDoors)
        {
            if (baseState->numDoors > 1)
            {
                testState = baseState->clone();
                testState->numDoors--;
                evaluate(testState, mazes, instances);
                MazeList.push_back(testState);
            }
        }
        i = (baseState->numDoors + 1) - numDoors;
        if (i < 0) i = -i;
        if (deltaDoors == -1 || i <= deltaDoors)
        {
            testState = baseState->clone();
            testState->numDoors++;
            evaluate(testState, mazes, instances);
            MazeList.push_back(testState);
        }

        // Vary goals.
        i = (baseState->numGoals - 1) - numGoals;
        if (i < 0) i = -i;
        if (deltaGoals == -1 || i <= deltaGoals)
        {
            if (baseState->numGoals > 1)
            {
                testState = baseState->clone();
                testState->numGoals--;
                evaluate(testState, mazes, instances);
                MazeList.push_back(testState);
            }
        }
        i = (baseState->numGoals + 1) - numGoals;
        if (i < 0) i = -i;
        if (deltaGoals == -1 || i <= deltaGoals)
        {
            testState = baseState->clone();
            testState->numGoals++;
            evaluate(testState, mazes, instances);
            MazeList.push_back(testState);
        }

        // Vary context level sizes.
        for (i = 0, j = baseState->contextSizes.size(); i < j; i++)
        {
            k = (baseState->contextSizes[i] - 1) - contextSizes[i];
            if (k < 0) k = -k;
            if (deltaContextSizes.size() == 0 || k <= deltaContextSizes[i])
            {
                if (baseState->contextSizes[i] > 1)
                {
                    testState = baseState->clone();
                    testState->contextSizes[i]--;
                    evaluate(testState, mazes, instances);
                    MazeList.push_back(testState);
                }
            }
            k = (baseState->contextSizes[i] + 1) - contextSizes[i];
            if (k < 0) k = -k;
            if (deltaContextSizes.size() == 0 || k <= deltaContextSizes[i])
            {
                testState = baseState->clone();
                testState->contextSizes[i]++;
                evaluate(testState, mazes, instances);
                MazeList.push_back(testState);
            }
        }

        // Vary effect delay scale.
        i = (baseState->effectDelayScale - 1) - effectDelayScale;
        if (i < 0) i = -i;
        if (deltaEffectDelayScale == -1 || i <= deltaEffectDelayScale)
        {
            if (baseState->effectDelayScale > 1)
            {
                testState = baseState->clone();
                testState->effectDelayScale--;
                evaluate(testState, mazes, instances);
                MazeList.push_back(testState);
            }
        }
        i = (baseState->effectDelayScale + 1) - effectDelayScale;
        if (i < 0) i = -i;
        if (deltaEffectDelayScale == -1 || i <= deltaEffectDelayScale)
        {
            testState = baseState->clone();
            testState->effectDelayScale++;
            evaluate(testState, mazes, instances);
            MazeList.push_back(testState);
        }

        // Select and sort mazes.
        work.clear();
        for (j = 0; j < numOutput;)
        {
            bestState = NULL;
            for (itr = MazeList.begin(); itr != MazeList.end(); itr++)
            {
                if (bestState == NULL || (*itr)->score > bestState->score)
                {
                    bestState = *itr;
                }
            }
            if (bestState == NULL) break;
            for (itr = work.begin(); itr != work.end(); itr++)
            {
                if (bestState->equals(*itr)) break;
            }
            if (itr == work.end())
            {
                work.push_back(bestState);
                j++;
            }
            MazeList.remove(bestState);
        }
        for (itr = MazeList.begin(); itr != MazeList.end(); itr++)
        {
            delete *itr;
        }
        MazeList.clear();
        for (itr = work.begin(); itr != work.end(); itr++)
        {
            MazeList.push_back(*itr);
        }
    }

    // Print generated mazes.
    printf("Generated maze parameter states:\n");
    for (itr = MazeList.begin(); itr != MazeList.end(); itr++)
    {
        if ((*itr)->score > 0.0)
        {
            printf("====================================\n");
            (*itr)->print();
        }
    }
    printf("====================================\n");

    // Dump mona-format files?
    if (monaPrefix != NULL) dumpMonaFiles(monaPrefix);

    // Dump SNNS-format files?
    if (snnsPrefix != NULL) dumpSNNSfiles(snnsPrefix);

    return 0;
}


// Evaluate a parameter state.
// Generate a number of meta-mazes for the given state;
// for each meta-maze determine an "interest" score
// by generating instances of the meta-maze and
// recording the success, variety, and length of
// the goal paths in them.
void evaluate(MazePathFinder *testState, int mazes, int instances)
{
    int i,j;
    RANDOM bestSeed;
    double bestScore;

    bestScore = -1.0;
    bestSeed = 0;
    for (i = 0; i < mazes; i++)
    {
        // Create and evaluate a meta-maze.
        testState->metaSeed = randomizer->RAND();
        testState->instanceSeeds.clear();
        testState->instanceFrequencies.clear();
        for (j = 0; j < instances; j++)
        {
            testState->instanceSeeds.push_back(testState->metaSeed + j);
            testState->instanceFrequencies.push_back(1.0);
        }
        testState->evaluate();

        if (bestScore < 0.0 || testState->score > bestScore)
        {
            bestScore = testState->score;
            bestSeed = testState->metaSeed;
        }
    }

    // Save the best meta-maze, "condensing" it so that
    // all instances yield goal paths.
    testState->score = bestScore;
    testState->metaSeed = bestSeed;
    while (testState->goalInstances.size() < testState->instanceSeeds.size())
    {
        testState->instanceSeeds.clear();
        testState->instanceFrequencies.clear();
        for (i = 0, j = testState->goalInstances.size(); i < j; i++)
        {
            testState->instanceSeeds.push_back(testState->goalInstances[i]);
            testState->instanceFrequencies.push_back(1.0);
        }
        testState->evaluate();
    }
}


// Dump generated mazes as Mona-format input files.
void dumpMonaFiles(char *monaPrefix)
{
    int i;
    FILE *fp;
    char buf[100];
    list<MazePathFinder *>::iterator itr;

    i = 0;
    for (itr = MazeList.begin(); itr != MazeList.end(); itr++)
    {
        sprintf(buf, "%s%d.pat", monaPrefix,i);
        if ((fp = fopen(buf, "w")) == NULL)
        {
            fprintf(stderr, "Cannot open file %s\n", buf);
            exit(1);
        }
        (*itr)->dumpMonaFormat(fp);
        fclose(fp);
        i++;
    }
}


// Dump generated mazes as SNNS-format input files.
void dumpSNNSfiles(char *snnsPrefix)
{
    int i,j,k;
    FILE *fp;
    char buf[100];
    list<MazePathFinder *>::iterator itr;
    MazePathFinder *testState;

    for (i = 0, itr = MazeList.begin(); itr != MazeList.end(); itr++, i++)
    {
        testState = *itr;
        for (j = 0, k = testState->goalInstances.size(); j < k; j++)
        {
            sprintf(buf, "%s%d-%d.pat", snnsPrefix,i,j);
            if ((fp = fopen(buf, "w")) == NULL)
            {
                fprintf(stderr, "Cannot open file %s\n", buf);
                exit(1);
            }
            testState->dumpSNNSformat(j, fp);
            fclose(fp);
        }
    }
}