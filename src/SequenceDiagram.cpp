#include "SequenceDiagram.hpp"

// SequenceDiagramXML::SequenceDiagramXML() {}

SequenceDiagramXML::Message::Message(string name){
  this->name = name;
  this->orig = "";
  this->dest = "";
  this->prob = numeric_limits<double>::quiet_NaN();
}

void SequenceDiagramXML::Message::setOrig(SequenceDiagramXML seq, string orig_lifeline){
  vector<string> all_lifelines = seq.getAllLifelines();

  if(find(all_lifelines.begin(),all_lifelines.end(), orig_lifeline) != all_lifelines.end()){
    this->orig = orig_lifeline;
  }
  else{
    throw std::invalid_argument("MessageFormatException");
  }
}

void SequenceDiagramXML::Message::setDest(SequenceDiagramXML sd, string dest_lifeline){
  std::vector<string> all_lifelines = sd.getAllLifelines();

  if(find(all_lifelines.begin(),all_lifelines.end(), dest_lifeline) != all_lifelines.end()){
    this->dest = dest_lifeline;
  }
  else{
    throw std::invalid_argument("MessageFormatException");
  }
}

void SequenceDiagramXML::Message::setProb(double prob){
  this->prob = prob;
}


string SequenceDiagramXML::Message::getName(){
  return this->name;
}

string SequenceDiagramXML::Message::getOrig(){
  return this->orig;
}

string SequenceDiagramXML::Message::getDest(){
  return this->dest;
}

double SequenceDiagramXML::Message::getProb(){
  return this->prob;
}

SequenceDiagramXML::Fragment::Fragment(string name){
  this->name = name;
}

void SequenceDiagramXML::Fragment::setSeqDiagram(SequenceDiagramXML sd, string seq_diagram){
  vector<string> all_names = sd.getAllDiagramName();
  
  if(find(all_names.begin(), all_names.end(), seq_diagram) != all_names.end()){
    this->seq_diagram_name = seq_diagram;
  }
  else{
    throw std::invalid_argument("EmptyOptionalFragment");
  }
}

string SequenceDiagramXML::Fragment::getSeqDiagram(){
  return this->seq_diagram_name;
}

string SequenceDiagramXML::Fragment::getName(){
  return this->name;
}

SequenceDiagramXML::SequenceDiagram::SequenceDiagram(string name) {
  this->name = name;	
}

string SequenceDiagramXML::SequenceDiagram::getName() {
	return this->name;
}

void SequenceDiagramXML::SequenceDiagram::addLifelines(string lifeline){
  this->lifelines.push_back(lifeline);
}

void SequenceDiagramXML::SequenceDiagram::addMessage(SequenceDiagramXML::Message message){
  if(message.getName().empty() || message.getOrig().empty() || message.getDest().empty() || isnan(message.getProb())){
    throw std::invalid_argument("MessageFormatException");
  }
  else{
    this->messages.push_back(message);
    //cout << "addSequenceDiagramXML::Message() this->messages.size() " << this->messages.size() << endl;
  }
}

void SequenceDiagramXML::SequenceDiagram::addFragment(SequenceDiagramXML::Fragment fragment){
  if(fragment.getName().empty() || fragment.getSeqDiagram().empty()){
    throw std::invalid_argument("EmptyOptionalFragment");
  }
  else{
    this->fragments.push_back(fragment);
  }
}

vector<string> SequenceDiagramXML::SequenceDiagram::getLifelines(){
  return this->lifelines;
}

vector<SequenceDiagramXML::Message> SequenceDiagramXML::SequenceDiagram::getMessages(){
  //cout << "getSequenceDiagramXML::Messages() this->messages.size() " << this->messages.size() << endl;
  return this->messages;
}

vector<SequenceDiagramXML::Fragment> SequenceDiagramXML::SequenceDiagram::getFragments(){
  return this->fragments;
}

std::vector<string> SequenceDiagramXML::getAllLifelines(){
  std::vector<string> all_lifelines;
  for(SequenceDiagramXML::SequenceDiagram* sd: this->getAllDiagram()){
    for(string& s: sd->getLifelines()){
      all_lifelines.push_back(s);
    }
  }

  return all_lifelines;
}

std::vector<SequenceDiagramXML::Message> SequenceDiagramXML::getAllMessages(){
  std::vector<SequenceDiagramXML::Message> all_message;
  for(SequenceDiagramXML::SequenceDiagram* s: this->getAllDiagram()){
    //cout << s->getName() << endl;
    for(SequenceDiagramXML::Message& m: s->getMessages()){
      all_message.push_back(m);
    }
  }
  return all_message;
}

std::vector<SequenceDiagramXML::Fragment> SequenceDiagramXML::getAllFragments(){
  std::vector<SequenceDiagramXML::Fragment> all_fragment;
  for(SequenceDiagramXML::SequenceDiagram* s: this->getAllDiagram()){
    for(SequenceDiagramXML::Fragment& f: s->getFragments()){
      all_fragment.push_back(f);
    }
  }
  return all_fragment;
}

vector<string> SequenceDiagramXML::getAllDiagramName(){
  vector<string> all_names;
  for(SequenceDiagramXML::SequenceDiagram* s: this->getAllDiagram()){
    all_names.push_back(s->getName());
  }

  return all_names;
}

vector<SequenceDiagramXML::SequenceDiagram*> SequenceDiagramXML::getAllDiagram(){
  return this->seq_diagrams;
}

void SequenceDiagramXML::addDiagram(SequenceDiagramXML::SequenceDiagram* qqn) {
  this->seq_diagrams.push_back(qqn);
}

string SequenceDiagramXML::SequenceDiagramXML::toXML(){
  stringstream str_stream;

  str_stream << "<SequenceDiagrams>\n";

  str_stream << "\t<Lifelines>\n";
  vector<string> all_lifelines = this->getAllLifelines();

  for(string& s: all_lifelines){
    str_stream << "\t\t<Lifeline name=\"" << s << "\" />\n";
  }

  str_stream << "\t</Lifelines>\n";

  str_stream << "\t<Fragments>\n";
  vector<SequenceDiagramXML::Fragment> f = this->getAllFragments();

  for(SequenceDiagramXML::Fragment& fg: f){
    str_stream << "\t\t<Optional name=\"" << fg.getName() << "\" representedBy=\"" << fg.getSeqDiagram() << "\" />\n";
  }

  str_stream << "\t</Fragments>\n";

  vector<SequenceDiagramXML::SequenceDiagram*>sd = this->getAllDiagram();

  for(SequenceDiagramXML::SequenceDiagram* s: sd){
    str_stream << "\t<SequenceDiagram name=\"" << s->getName() << "\">\n";
    for(SequenceDiagramXML::Message& m: s->getMessages()){
      str_stream << "\t\t<Message name=\"" << m.getName() << "\" prob=\"" << m.getProb() << "\" source=\"" << m.getOrig() << "\" target=\"" << m.getDest() << "\" />\n";
    }
    for(SequenceDiagramXML::Fragment& fr: s->getFragments()){
      str_stream << "\t\t<Fragment name=\"" << fr.getName() << "\" />\n";
    }
    str_stream << "\t</SequenceDiagram>\n";
  }
  
  str_stream << "</SequenceDiagrams>";

  return str_stream.str();

}

int SequenceDiagramXML::exportXML(){
  std::ofstream out;
  auto xml = this->toXML();
  out.open("SequenceDiagram.xml");
  out << xml;
  out.close();
  return 1;
}
