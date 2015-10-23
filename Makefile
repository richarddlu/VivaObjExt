LIBS = \
	-lopencv_core \
	-lopencv_video \
	-lopencv_highgui \
	-lopencv_imgproc

FLAGS = --std=c++11

all:	VivaObjExt

VivaObjExt:	VivaObjExt.o voting_segmenter.o mog_background_subtracter.o mog2_background_subtracter.o grid_seams.o
			g++ VivaObjExt.o voting_segmenter.o mog_background_subtracter.o mog2_background_subtracter.o grid_seams.o -o VivaObjExt $(LIBS) $(FLAGS)

VivaObjExt.o:	VivaObjExt.cpp
				g++ -c VivaObjExt.cpp $(FLAGS)

voting_segmenter.o:	voting_segmenter.cpp
					g++ -c voting_segmenter.cpp $(FLAGS)

mog_background_subtracter.o:	mog_background_subtracter.cpp
								g++ -c mog_background_subtracter.cpp $(FLAGS)

mog2_background_subtracter.o:	mog2_background_subtracter.cpp
								g++ -c mog2_background_subtracter.cpp $(FLAGS)

grid_seams.o:	grid_seams.cpp
				g++ -c grid_seams.cpp $(FLAGS)

clean:
	rm -f VivaObjExt VivaObjExt.o voting_segmenter.o mog_background_subtracter.o mog2_background_subtracter.o grid_seams.o
