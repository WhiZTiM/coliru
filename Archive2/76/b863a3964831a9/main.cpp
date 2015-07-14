      	
			     								                        |
												                        | RGBA
												                        |
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
|       | Y_1                   | Y_n                 |     | U_1                  | U_n                   |     | V_1                  | V_n
|       |                       |                     |     |                      |                       |     |                      |
|     Remap        ...        Remap                   |   Remap        ...       Remap                     |   Remap        ...       Remap
|     	|                       |                     |     |                      |                       |     |                      |
| ______| Y_1_r            _____| Y_n_r               |     | U_1_r                | U_1_r                 |     | V_1_r                | V_n_r
| |     |                 |     |                     |_____|______________________|                       |_____|______________________|
| | ROIExtract     ...    | ROIExtract                                  |                                                   |
| |     |                 |     |                                  ROICombine                                          ROICombine
| |     | Y_1_r_R         |     | Y_n_r_R                               |                                                   |
| |		|                 |     |                                       | U_r                                               | V_r
| |EqualizeHist    ...    |EqualizeHist                                 |                                                   |
| |     |                 |     |                                       |                                                   |
| |     | Y_1_r_R_eq      |     | Y_n_r_R_eq                            |                                                   |
| |_____|                 |_____|                                       |                                                   |
|       |                       |                                       |                                                   |
|  ROICombine      ...     ROICombine                                   |                                                   |
|       |                       |                                       |                                                   |
|       | Y_1_r_eq              | Y_n_r_eq                              |                                                   |      
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