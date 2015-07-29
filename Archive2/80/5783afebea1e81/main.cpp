
//=--- File structure ---=

 Api
  |- ApiManager.h
  |- ApiManager.m
  |- ApiClient.h
  |- ApiClient.m
//=--- File structure ---=

//=--------------------------------------------------------------------------------------------- Log ---=
/Api/ApiClient.m::: error: unexpected interface name 'NSData': expected expression
                NSData* callerData = [@"http://nikyotis.xyz" dataUsingEncoding:NSUTF8StringEncoding];
                ^
/Api/ApiClient.m::: error: use of undeclared identifier 'callerData'
                NSData* callerData = [@"http://nikyotis.xyz" dataUsingEncoding:NSUTF8StringEncoding];
//=--------------------------------------------------------------------------------------------- Log ---=

//=--------------------------------------------------------------------------------------------- Source ---=

  //=--------------------------------------------------------------------------- Api/ApiManager.h ----=
#import <Foundation/Foundation.h>
#import "AFURLResponseSerialization.h"
#import <AFNetworking/AFNetworking.h>

// COMMENT (nik)
    // ApiManager implemented as a Singleton
    // check potential issues this might cause
    // http://stackoverflow.com/questions/24883506/ios-connect-to-server-via-singleton-implementation
// COMMENT (nik)
static NSString *const kYoBaseUrl = @"http://nikyotis.xyz";

    // AFNetworking-1.0's AFHTTPClient was replaced in AFNetworking-2.0 with
    // either AFHTTPRequestOperationManager or AFHTTPSessionManager
    // https://github.com/AFNetworking/AFNetworking/wiki/AFNetworking-2.0-Migration-Guide#afhttpclient--afhttprequestoperationmanager--afhttpsessionmanager

@interface ApiManager : AFHTTPRequestOperationManager
    // COMMENT (nik)
        // alternative to AFHTTPRequestOperationManager    
        // @interface ApiManager : AFHTTPSessionManager
    // COMMENT (nik)

+ (ApiManager *)sharedManager;

@end
  //=--------------------------------------------------------------------------- Api/ApiManager.h --------=

  //=--------------------------------------------------------------------------- Api/ApiManager.m --------=
#import "ApiManager.h"
#import "AFNetworking.h"

@implementation ApiManager

#pragma mark - Methods
#pragma mark - Initialization

- (id)initWithBaseURL:(NSURL *)url {
    
    self = [super initWithBaseURL:url];
    if (!self) {
        return nil;
    }

  //=---------------------------------------------------------------- GET -----=
  // https://github.com/AFNetworking/AFNetworking/wiki/AFNetworking-2.0-Migration-Guide#afhttprequestoperationmanager-example
    
  AFHTTPRequestOperationManager* manager =
    [AFHTTPRequestOperationManager manager];
  manager.responseSerializer = [AFJSONResponseSerializer serializer];
    
        //  manager.requestSerializer = [AFJSONRequestSerializer serializer];
        //  [manager.requestSerializer setValue:@"application/json"
        //                   forHTTPHeaderField:@"X-I do what I want"];

  [manager GET:@"http://nikyotis.xyz"
      parameters:nil
      success:^(AFHTTPRequestOperation *operation, id responseObject) {
    	  NSLog(@"JSON: %@", responseObject);
      }
      failure:^(AFHTTPRequestOperation *operation, NSError *error) {
		  NSLog(@"Error: %@", error);
      }];
  //=---------------------------------------------------------------- GET -----=
	
  //=---------------------------------------------------------------- POST ----=
    
    [manager POST:@"http://nikyotis.xyz"
       parameters:@{
                    @"color" : @"green"
                    }
          success:^(AFHTTPRequestOperation *operation, id responseObject) {
              NSLog(@"JSON: %@", responseObject);
          }
          failure:^(AFHTTPRequestOperation *operation, NSError *error) {
              NSLog(@"Error: %@", error);
          }];
  //=---------------------------------------------------------------- POST ----=
	
  return self;
}

#pragma mark - Singleton Methods

+ (ApiManager *)sharedManager {
  static dispatch_once_t pred;
  static ApiManager *_sharedManager = nil;

  dispatch_once(&pred, ^{
    _sharedManager = [[self alloc]
        initWithBaseURL:[NSURL URLWithString:kYoBaseUrl]];
  });
  return _sharedManager;
}

@end
  //=--------------------------------------------------------------------------- Api/ApiManager.m --------=


  //=--------------------------------------------------------------------------- Api/ApiClient.h --------=

#import <Foundation/Foundation.h>

@class Result;
@class MeasureLabels;
@class AFHTTPRequestOperation;

@interface ApiClient : NSObject

+ (Result *)parseResultWithId:(NSString *)id
                  andResponse:(NSDictionary *)response;

+ (MeasureLabels *)parseMeasureLabelsResponse:(NSDictionary *)response;

- (void)fetchResultByIdentifier:(NSString *)resultIdentifier
                        success:(void (^)(Result *result))success
                        failure:(void (^)(AFHTTPRequestOperation *operation,
                                          NSError *error))failure;

- (void)fetchMeasureLabelsWithSuccess:(void (^)(MeasureLabels *labels))success
                              failure:
                                  (void (^)(AFHTTPRequestOperation *operation,
                                            NSError *error))failure;

- (void)uploadFrontData:(NSData *)fontData
               sideData:(NSData *)sideData
        success:(void (^)(NSString *id, NSNumber *wait))success
                failure:(void (^)(AFHTTPRequestOperation *operation,
                                  NSError *error))failure
               progress:(void (^)(NSNumber *progress))progress;

@end
  //=--------------------------------------------------------------------------- Api/ApiClient.h --------=

  //=--------------------------------------------------------------------------- Api/ApiClient.m --------=
#import "ApiClient.h"
#import <AFNetworking.h>
#import "Result.h"
#import "ApiManager.h"
#import "Measure.h"
#import "MeasureLabels.h"
#import "UrlUtils.h"
#import "StringUtils.h"

#import "AFURLResponseSerialization.h"

#import <Foundation/NSData.h>
#import <Foundation/NSString.h>
    // or just
    // @import Foundation; 
    // for NSData.h, NSString.h

@implementation ApiClient


+ (Result *)parseResultWithId:(NSString *)id
                  andResponse:(NSDictionary *)response {
  Result* result = [Result resultWithId:id];
  result.date = [NSDate date];

  NSDictionary* measurements =
      [ [response objectForKey:@"meta"] objectForKey:@"measurements"];
  for (NSString* key in measurements.allKeys) {
    
    NSDictionary* jsonMeasure = [measurements valueForKey:key];
    NSNumber* value = [jsonMeasure valueForKey:@"value"];
    NSNumber* factor = [jsonMeasure valueForKey:@"factor"];
    NSString* unit = [jsonMeasure valueForKey:@"unit"];
    Measure* measure = [Measure measureWithId:key value:value unit:unit];
    [result.measures addObject:measure];
    if (factor != nil) {
      measure.factor = factor;
    }
  }

  return result;
}

+ (MeasureLabels* )parseMeasureLabelsResponse:(NSDictionary *)response {
  MeasureLabels* labels = [[MeasureLabels alloc] initWithLabels:response];
  return labels;
}

- (void)fetchResultByIdentifier:(NSString *)resultIdentifier
                        success:(void (^)(Result *result))success
                        failure:(void (^)(AFHTTPRequestOperation *operation,
                                          NSError *error))failure {
  NSDictionary *parameters = [NSDictionary
      dictionaryWithObjectsAndKeys:resultIdentifier, @"i", @"json", @"f", nil];
  [ [ApiManager sharedManager]
             GET:@"/api/get/"
      parameters:parameters
         success:^(AFHTTPRequestOperation *operation, NSDictionary *response) {
           Result *result =
               [QuantaCorpApiClient parseResultWithId:resultIdentifier
                                          andResponse:response];
           success(result);
         }
         failure:failure];
}

- (void)fetchMeasureLabelsWithSuccess:(void (^)(MeasureLabels *labels))success
                              failure:
                                  (void (^)(AFHTTPRequestOperation *operation,
                                            NSError *error))failure {
  NSDictionary *parameters = [NSDictionary
      dictionaryWithObjectsAndKeys:@"all", @"m", @"json", @"f", nil];
  [[ApiManager sharedManager]
             GET:@"/api/get/"
      parameters:parameters
         success:^(AFHTTPRequestOperation *operation, NSDictionary *response) {
           MeasureLabels *labels =
               [QuantaCorpApiClient parseMeasureLabelsResponse:response];
           success(labels);
         }
         failure:failure];
}

- (void)uploadFrontData:(NSData *)fontData
               sideData:(NSData *)sideData
        success:(void (^)( NSString *id, NSNumber *wait ) )success
                failure:(void (^)( AFHTTPRequestOperation *operation,
                                  NSError *error ) )failure
               progress:(void (^)( NSNumber *progress ) )progress {   
        
    // http://stackoverflow.com/questions/23546572/afnetworking-2-0-implementation-code-not-working
    // prepare a POST request by creating an NSMutableURLRequest instance using
    // the parameters we want to send via POST

    
// AFNetworking 2.0 Convenience Methods
    // https://github.com/AFNetworking/AFNetworking/wiki/AFNetworking-2.0-Migration-Guide#afhttprequestoperationmanager--afhttpsessionmanager-convenience-methods-afnetworking-20
    
    //- (NSURLSessionDataTask *)POST:(NSString *)URLString
    //                    parameters:(NSDictionary *)parameters
    //                       success:(void (^)(NSURLSessionDataTask *, id))success
    //                       failure:(void (^)(NSURLSessionDataTask *, NSError *))failure
    //
    //- (NSURLSessionDataTask *)POST:(NSString *)URLString
    //                    parameters:(NSDictionary *)parameters
    //     constructingBodyWithBlock:(void (^)(id <AFMultipartFormData>))block
    //                       success:(void (^)(NSURLSessionDataTask *, id))success
    //                       failure:(void (^)(NSURLSessionDataTask *, NSError *))
// AFNetworking 2.0 Convenience Methods

//    NSMutableURLRequest* request = nil;
//    [ [ApiManager sharedManager] POST:"/v1/exec"
//                           parameters:nil
//            constructingBodyWithBlock:( void (^) (id<AFMultipartFormData> formData) )
//                              success:( void (^) (AFHTTPRequestOperation *operation, id responseObject) )
//                              failure:( void (^) (AFHTTPRequestOperation *operation, NSError *error) ) {

  NSMutableURLRequest* request = 
    [ [ApiManager sharedManager] POST:"/v1/exec"
                           parameters:nil
            constructingBodyWithBlock:( void (^) (id<AFMultipartFormData> formData) )
                              success:( void (^) (AFHTTPRequestOperation *operation, id responseObject) )
                              failure:( void (^) (AFHTTPRequestOperation *operation, NSError *error) ) {
        
                //NSData* callerData = [[NSData alloc] init];                  
                NSData* callerData = [@"http://nikyotis.xyz" dataUsingEncoding:NSUTF8StringEncoding];
                [formData appendPartWithFormData:callerData name:@"caller"];
                [formData appendPartWithFileData:fontData name:@"front" fileName:@"front" mimeType:@"application/octet-stream"];
                [formData appendPartWithFileData:sideData name:@"side" fileName:@"side" mimeType:@"application/octet-stream"];
            } ];
    
          AFHTTPRequestOperation* operation =
      [[AFHTTPRequestOperation alloc] initWithRequest:request];
    [operation setUploadProgressBlock:^(NSUInteger bytesWritten,
                      long long totalBytesWritten,
                      long long totalBytesExpectedToWrite) {

    double progressPercentage =
      (double)totalBytesWritten / (double)totalBytesExpectedToWrite;
    NSNumber *progressPercentageNumber =
      [NSNumber numberWithDouble:progressPercentage];
    progress(progressPercentageNumber);
    }];

    [operation setCompletionBlockWithSuccess:^(AFHTTPRequestOperation *operation,
                         NSData *responseData) {
    NSError *error;
    NSDictionary *response =
      [NSJSONSerialization JSONObjectWithData:responseData
                      options:NSJSONReadingMutableContainers
                        error:&error];
    int status = [[response objectForKey:@"state"] intValue];

    if (status == 0 || status == 1) {
      NSString *id = [response objectForKey:@"unique_id"];
      NSNumber *wait = [response objectForKey:@"wait"];
      success(id, wait);
    } else {
      NSDictionary *userInfo =
        [NSDictionary dictionaryWithObject:@"Api return error"
                      forKey:NSLocalizedDescriptionKey];
      NSError *error = [[NSError alloc] initWithDomain:@"io.quantacorp"
                            code:1
                          userInfo:userInfo];
      failure(operation, error);
    }
    } failure:^(AFHTTPRequestOperation *operation, NSError *error) {
    NSLog(@"Failure %@ %@", operation, error);
    failure(operation, error);
    }];

    [operation start];
}

@end
  //=--------------------------------------------------------------------------- Api/ApiClient.m --------=

//=--------------------------------------------------------------------------------------------- Source ---=