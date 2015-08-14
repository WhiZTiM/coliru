
//
// Create graph
//

vx_graph graph = nvxCreateStreamGraph(context);
NVXIO_CHECK_REFERENCE(graph);

//
// Create data objects
//

vx_image yuvImage = vxCreateVirtualImage(graph, width, height, VX_DF_IMAGE_NV12);
NVXIO_CHECK_REFERENCE(yuvImage);

vx_image yImage = nvxCreateImageFromChannel(yuvImage, VX_CHANNEL_Y);
NVXIO_CHECK_REFERENCE(yImage);

const std::vector<vx_image> splittedYImage = splitImage(yImage, cameraNumber, border);

vx_image equalizedImage = vxCreateVirtualImage(graph, 0, 0, VX_DF_IMAGE_VIRT);
NVXIO_CHECK_REFERENCE(equalizedImage);

vx_image outputImage = vxCraeteImage(context, width, height, VX_DF_IMAGE_RGBX);
NVXIO_CHECK_REFERENCE(outputImage);

//
// Create nodes
//

vx_node colorConvertInNode = vxColorConvertNode(graph, outputImage, yuvImage);
NVXIO_CHECK_REFERENCE(colorConvertInNode);

std::vector<vx_node> equalizeHistNodes(cameraNumber);
std::vector<vx_node> copyImageNodes(cameraNumber);
for (std::size_t i = 0; i != cameraNumber; ++i)
{
    equalizeHistNodes[i] = vxEqualizeHistNode(graph, splittedYImage[i], equalizedImage);
    NVXIO_CHECK_REFERENCE(equalizedHistNodes[i]);
    
    copyImageNodes[i] = nvxCopyImageNode(graph, equalizedImage, splittedYImage[i]);
    NVXIO_CHECK_REFERENCE(copyImageNodes[i]);
}

vx_node colorConvertOutNode = vxColorConvertNode(graph, yuvImage, outputImage);
NVXIO_CHECK_REFERENCE(colorConvertOutNode);

//
// Release data objects
//

NVXIO_SAFE_CALL(vxReleaseImage(&equalizedImage));

for (std::size_t i = 0; i != cameraNumber; ++i)
{
    NVXIO_SAFE_CALL(vxReleaseImage(&splittedYImage[i]));    
}

NVXIO_SAFE_CALL(vxReleaseImage(&yImage));
NVXIO_SAFE_CALL(vxReleaseImage(yuvImage));

//
// Release nodes
//

NVXIO_SAFE_CALL(vxReleaseNode(&colorConvertOutNode));

for (std::size_t i = 0; i != cameraNumber; ++i)
{
    NVXIO_SAFE_CALL(vxReleaseNode(&copyImageNodes[i]));
    NVXIO_SAFE_CALL(vxReleaseNode(&equalizeHistNodes[i]));
}

//
// Verify graph
//

NVXIO_SAFE_CALL(vxVerifyGraph(graph));

//
// ...
//

// Got Cuda-mapped inputImage here

if (process)
{
    // Set inputImage as graph input
    NVXIO_SAFE_CALL(vxSetParameterByIndex(colorConvertInNode, 0, inputImage));
   
    // Process graph
    NVXIO_SAFE_CALL(vxProcessGraph(graph));
    
    // Render outputImage
}
else
{
    // Render inputImage
}

//
// ...
//

//
// Release remaing resources
//

NVXIO_SAFE_CALL(vxReleaseNode(&colorConvertInNode));

NVXIO_SAFE_CALL(vxReleaseImage(&outputImage));

NVXIO_SAFE_CALL(vxReleaseGraph(&graph));
