      	
	r   - remapped 								                        |
	R   - ROI									                        | RGBA
	eq  - histogram equalized					                        |
                        	           	                           ColorConvert
                            	       			                        |
                                	   			                        | IYUV
            		____________________________________________________|____________________________________________________
            		|                                                   |                                                    |
       	      ChannelExtract                                      ChannelExtract                                       ChannelExtract
                	|                                                   |                                                    |
                	| Y                                                 | U                                                  | V
________ ___________|___________                      __________________|___________                       __________________|__________
|       |                       |                     |     |                      |                       |     |                      |
|   ROIExtract     ...      ROIExtract                | ROIExtract     ...     ROIExtract                  | ROIExtract     ...     ROIExtract
|       |	                    |                     |     |                      |                       |     |                      |
|       | Y_R1                  | Y_Rn                |     | U_R1                 | U_Rn                  |     | V_R1                 | V_Rn
|       |                       |                     |     |                      |                       |     |                      |
|     Remap        ...        Remap                   |   Remap        ...       Remap                     |   Remap        ...       Remap
|     	|                       |                     |     |                      |                       |     |                      |
| ______| Y_R1_r           _____| Y_Rn_r              |     | U_R1_r               | U_R1_r                |     | V_R1_r               | V_Rn_r
| |     |                 |     |                     |_____|______________________|                       |_____|______________________|
| | ROIExtract     ...    | ROIExtract                                  |                                                   |
| |     |                 |     |                                  ROICombine                                          ROICombine
| |     | Y_R1_r_R        |     | Y_Rn_r_R                              |                                                   |
| |		|                 |     |                                       | U_r                                               | V_r
| |EqualizeHist    ...    |EqualizeHist                                 |                                                   |
| |     |                 |     |                                       |                                                   |
| |     | Y_R1_r_R_eq     |     | Y_Rn_r_R_eq                           |                                                   |
| |_____|                 |_____|                                       |                                                   |
|       |                       |                                       |                                                   |
|  ROICombine      ...     ROICombine                                   |                                                   |
|       |                       |                                       |                                                   |
|       | Y_R1_r_eq             | Y_Rn_r_eq                             |                                                   |      
|_______|_______________________|                                       |                                                   |
                    |                                                   |                                                   |
               ROICombine                                               |                                                   |
                    |                                                   |                                                   |
                    | Y_r_eq                                            |                                                   |
                    |___________________________________________________|___________________________________________________|
                                                                        |
                                                                  ChannelCombine
                                                                        |
                                                                        | IYUV_r_eq
                                                                        |
                                                                   ColorConvert
                                                                        |
                                                                        | RGBA_r_eq
                                                                        |