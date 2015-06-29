
<!DOCTYPE html>
<html>
<head>

    <title>Coliru History</title>
    <style type="text/css">

        html, body, textarea {
            position: relative;
            font-family: monospace;
            width: 100%;
            height: 100%;
        }
        body { 
            overflow: scroll;
        }

        h1 { margin: 8px; }
        h2 { margin: 12px; }

        #page {
            position: relative;
            width: 100%;
            height: 100%;
        }

        .margin {
            min-width: 20px;
            padding: 40px;
        }

        textarea {
            border: 0; /*1px solid gray;*/
            min-width: 800px;
            max-width: 800px;
            outline: 0 !important;
            appearance: none;
            -webkit-appearance: none;
            -moz-appearance: none;
        }


        .hbox {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            padding: 0;
            margin: 0;
            box-orient: horizontal;
            -webkit-box-orient: horizontal;
            -moz-box-orient: horizontal;
            box-align: stretch;
            -webkit-box-align: stretch;
            -moz-box-align: stretch;
        }

        .vbox {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            padding: 0;
            margin: 0;
            box-orient: vertical;
            -webkit-box-orient: vertical;
            -moz-box-orient: vertical;
            box-align: stretch;
            -webkit-box-align: stretch;
            -moz-box-align: stretch;
        }

        .f0 {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            box-flex: 0.0;
            -webkit-box-flex: 0.0;
            -moz-box-flex: 0.0;
        }

        .f1 {
            display: box;
            display: -webkit-box;
            display: -moz-box;
            position: relative;
            box-flex: 1.0;
            -webkit-box-flex: 1.0;
            -moz-box-flex: 1.0;
        }

    </style>
    <script type="text/javascript" src="https://raw.github.com/timrwood/moment/2.0.0/min/moment.min.js"></script>
    <script>

        // Redirect www. to host domain.
        if (window.location.host.search(/^www./) === 0 || window.location.host.search(/^stacked/) === 0) {
            var host = window.location.hostname + "";
            host = host.replace(/^www./, "");
            host = host.replace(/^stacked/, "coliru.stacked");
            window.location.hostname = host;
        }


        window.http_get = function (url) {
            var x = new XMLHttpRequest();
            x.open("GET", url, false);
            x.send(null);
            return x.responseText;
        };


        window.onload = function () {

//            Element.prototype.createNBSP = function () {
//                this.appendChild(document.createTextNode("\u00a0"));
//            };
            Element.prototype.createChild = function (tagNamePath) {
                var result = this;
                var tagNames = tagNamePath.split("/");
                for (var i = 0; i < tagNames.length; ++i) {
                    var child = document.createElement(tagNames[i]);
                    result.appendChild(child);
                    result = child;
                }
                return result;
            };
            var getHistory = function () {
                var historyObj = localStorage['history_items'];
                if (historyObj === undefined) {
                    historyObj = '{}';
                } else if (historyObj === null) {
                    localStorage.clear();
                    historyObj = '{}';
                }

                return JSON.parse(historyObj);
            };
            var history = getHistory();

            var length = Object.keys(history).length;

            if (length === 1) {
                document.getElementById('h2').textContent = "There is currently " + length + " item in your history.";
            } else {
                document.getElementById('h2').textContent = "There are currently " + length + " items in your history.";
            }


            var bydate = [];
            for (var key in history) {
                if (history.hasOwnProperty(key))
                {
                    var obj = history["" + key];
                    bydate.push(JSON.stringify({ 'timestamp':obj.timestamp, 'url':obj.url, 'src':obj.src, 'cmd':obj.cmd, 'output':obj.output }));
                }
            }

            bydate.sort(function (a, b) {
                if (a !== b) {
                    if (a < b) {
                        return 1;
                    }
                    else {
                        return 0;
                    }
                }
                return -1;
            });

            for (var i = 0; i < bydate.length; ++i) {
                var obj = JSON.parse(bydate[i]);
                var url = obj.url;
                var c = document.getElementById('content');
                var a = c.createChild('div/strong/a');
                a.href = url;
                a.textContent = moment.unix(obj.timestamp / 1000).fromNow();

                var d = c.createChild('div');

                var cmd_field = d.createChild('div/textarea');
                cmd_field.setAttribute('readonly', 'true');

                cmd_field.textContent = obj.src + '\n\n\n' + obj.cmd + '\n' + obj.output;
                cmd_field.rows = Math.min(20, cmd_field.textContent.split('\n').length);
                cmd_field.setAttribute('style', 'overflow:hidden; background-color: #EEEEEE');
                cmd_field.onkeydown = function(e){
                    if (e.keyCode == 27) {
                        this.setAttribute('style', 'overflow:hidden; background-color: #EEEEEE');
                        var oldw = this.width;
                        document.body.style.overflow='scroll';
                        this.width = oldw;
                        this.blur();
                    }
                };
                cmd_field.onmouseup = function(){
                    this.select();
                    this.setAttribute('style', 'overflow-y:scroll; background-color: #EEEEEE');
                };
                cmd_field.onmousedown = function(){
                    document.body.style.overflow='hidden';
                    var textareas = document.getElementsByTagName('textarea');
                    for (var i = 0; i < textareas.length; ++i)
                    {
                        textareas[i].setAttribute('style', 'overflow:hidden; background-color: #EEEEEE');
                    }
                };
                d.createChild('br');
            }
        }
    </script>
</head>
<body class="vbox f1">
<h1>Coliru History</h1>
<h2 id="h2">Coliru History</h2>


<div class='hbox f1'>
    <div class='margin'></div>
    <div id="content" class="vbox f1"></div>
    <div class='margin'></div>
</div>
</body>
</html>