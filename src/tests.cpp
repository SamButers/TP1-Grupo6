#include "ActivityDiagram.hpp"
#include "Element.hpp"
#include "Transition.hpp"
#include <gtest/gtest.h>

TEST(ActivityDiagramCreationTest, DiagramCreation) {
	ActivityDiagram diagram("my_diagram");

	EXPECT_EQ("my_diagram", diagram.getName());
}

TEST(ActivityDiagramCreationTest, DiagramCreation2) {
	ActivityDiagram diagram("my_second_diagram");

	EXPECT_EQ("my_second_diagram", diagram.getName());
}

TEST(ActivityDiagramCreationTest, DiagramCreation3) {
	ActivityDiagram diagram("my_last_diagram");

	EXPECT_EQ("my_last_diagram", diagram.getName());
}

TEST(ElementCreationTest, ElementCreation) {
	Element element("ex_element","ex_type");

	EXPECT_EQ("ex_element", element.getName());
	EXPECT_EQ("ex_type", element.getType());
}

TEST(ElementCreationTest, ElementCreation2) {
	Element element("ex_element2","ex_type2");

	EXPECT_EQ("ex_element2", element.getName());
	EXPECT_EQ("ex_type2", element.getType());
}

TEST(ElementCreationTest, ElementCreation3) {
	Element element("ex_element3","ex_type3");

	EXPECT_EQ("ex_element3", element.getName());
	EXPECT_EQ("ex_type3", element.getType());
}

TEST(ElementXMLTest, ElementXML) {
	Element element("my_element", "StartNode");

	EXPECT_EQ("<StartNode name=\"my_element\" />", element.toXML());
}

TEST(ElementXMLTest, ElementXML2) {
	Element element("endnode", "EndNode");

	EXPECT_EQ("\t<EndNode name=\"endnode\" />", element.toXML(1));
}

TEST(ElementXMLTest, ElementXML3) {
	Element element("arrival", "MergeNode");

	EXPECT_EQ("<MergeNode name=\"arrival\" />", element.toXML());
}

TEST(TransitionCreationTest, TransitionCreation) {
	Transition transition("my_transition", "my_src_element","my_dest_element");

	EXPECT_EQ("my_transition", transition.getName());
	EXPECT_EQ("my_src_element", transition.getSrc());
	EXPECT_EQ("my_dest_element", transition.getDest());
}

TEST(TransitionCreationTest, TransitionCreation2) {
	Transition transition("my_transition2", "my_src_element2","my_dest_element2");

	EXPECT_EQ("my_transition2", transition.getName());
	EXPECT_EQ("my_src_element2", transition.getSrc());
	EXPECT_EQ("my_dest_element2", transition.getDest());
}

TEST(TransitionCreationTest, TransitionCreation3) {
	Transition transition("my_transition3", "my_src_element3","my_dest_element3");

	EXPECT_EQ("my_transition3", transition.getName());
	EXPECT_EQ("my_src_element3", transition.getSrc());
	EXPECT_EQ("my_dest_element3", transition.getDest());
}

TEST(TransitionXMLTest, TransitionXML) {
	Transition transition("my_transition", "my_src_element","my_dest_element");

	EXPECT_EQ("<Transition name=\"my_transition\" src=\"my_src_element\" dest=\"my_dest_element\" />", transition.toXML(0));
}

TEST(TransitionXMLTest, TransitionXML2) {
	Transition transition("my_transition2", "my_src_element2","my_dest_element2");

	EXPECT_EQ("<Transition name=\"my_transition2\" src=\"my_src_element2\" dest=\"my_dest_element2\" />", transition.toXML(0));
}

TEST(TransitionXMLTest, TransitionXML3) {
	Transition transition("my_transition3", "my_src_element3","my_dest_element3");

	EXPECT_EQ("<Transition name=\"my_transition3\" src=\"my_src_element3\" dest=\"my_dest_element3\" />", transition.toXML(0));
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}