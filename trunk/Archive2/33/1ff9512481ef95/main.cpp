// applyStrategy.cpp
// April/May 2015, bfilipek.com

#include <iostream>
#include <memory>

class IRenderableNode;

class IScaleToFitMethod
{
public:
    virtual void ScaleToFit(IRenderableNode *pNode) = 0;
};

class BasicScaleToFit : public IScaleToFitMethod
{
public:
	virtual void ScaleToFit(IRenderableNode *pNode) {
		std::cout << "BasicScaleToFit::ScaleToFit" << std::endl;
	}
};

class IRenderableNode
{
public:
  IRenderableNode(std::unique_ptr<IScaleToFitMethod> pMethod) :
    m_pScaleToFitMethod(std::move(pMethod)) { }

  virtual void Transform() = 0;

  void ScaleToFit() {
	m_pScaleToFitMethod->ScaleToFit(this);
  }
  
protected:
	std::unique_ptr<IScaleToFitMethod> m_pScaleToFitMethod;
};

class Picture : public IRenderableNode
{
public:
  using IRenderableNode::IRenderableNode;

  void Transform() { }
};

int main()
{
  Picture pic(std::make_unique<BasicScaleToFit>());
  pic.ScaleToFit();
}