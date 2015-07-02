#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/optional.hpp>

#include <vector>
#include <string>

#include <iostream>

enum class DataOrMetadata{DATA, METADATA};

template <typename OutputIterator, typename T>
bool generate(OutputIterator& sink, const std::vector<T>& ts){
  for(const auto& t : ts){
      if(!t.generate(sink)){
          return false;
      }
  }
  return true;
}

struct PhrasalGroupData{
  int previousNSentences;
  int nSentences;
  boost::optional<int> regionDepth;
  DataOrMetadata dataOrMetadata;
  bool isInnermost;
  int psortno;

  template <typename OutputIterator>
      bool generate(OutputIterator& sink) const {
          using boost::spirit::karma::generate;
          using boost::spirit::karma::lit;
          using boost::spirit::karma::int_;

          auto result = true;

          if(nSentences != previousNSentences){
              // precede all but the first by a space
              if(-1 != previousNSentences){
                  generate(sink, lit(' '));
              }
              generate(sink, "[[" << int_(nSentences) << '/');
          }
          else{
              generate(sink, lit('&'));
          }

          if(regionDepth){
              generate(sink, '(' << int_(*regionDepth) << ')');
          }

          auto dom =(dataOrMetadata == DataOrMetadata::METADATA ? 'm' : 'd');
          generate(sink, lit(dom));

          //generate(sink, parents);

          if(isInnermost){
              generate(sink, int_(psortno+1) << '+');
          }
          generate(sink, int_(psortno));


          return result;
      }
};

struct SentenceData{
  const std::string& languageCode;
  DataOrMetadata dataOrMetadata;
  std::vector<PhrasalGroupData> phrasalGroups;

  template <typename OutputIterator>
      bool generate(OutputIterator& sink) const {
          using boost::spirit::karma::generate;
          using boost::spirit::ascii::string;

          auto dom =(dataOrMetadata == DataOrMetadata::METADATA ? 'm' : 'd');

          auto result = true;

          result &= generate(sink, string(languageCode) << ' ' << dom << ' ');
          result &= generate(sink, phrasalGroups);

          return result;
      }
};

struct DumpData{
  int nWords;

  std::vector<SentenceData> sentenceData;

  std::string operator()() const {
      using boost::spirit::karma::int_;
      using boost::spirit::karma::generate;

      std::string result;
      std::back_insert_iterator<std::string> sink(result);

      generate(sink, int_(nWords) << '\n');
      generate(sink, sentenceData);

      return result;
  }
};

int main(){
    auto dd = DumpData{1,
            {
                SentenceData{"en", DataOrMetadata::DATA, {PhrasalGroupData{-1, 1, boost::none, DataOrMetadata::DATA, false, 1},PhrasalGroupData{1, 1, boost::none, DataOrMetadata::DATA, false, 11}}},
                SentenceData{"it", DataOrMetadata::METADATA, {PhrasalGroupData{-1, 1, boost::none, DataOrMetadata::DATA, false, 1}}}
            }
        };
    
    std::cout << dd() << std::endl;
    
    return 0;
}
